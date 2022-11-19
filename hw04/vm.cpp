#include "vm.h"

#include <iostream>
#include <limits>

#include "util.h"

namespace vm {

vm_state create_vm(bool debug)
{
    vm_state state;
    state.next_op_id = 0;

    // enable vm debugging
    state.debug = debug;

    register_instruction(state, "PRINT", [](vm_state& vmstate, const item_t /*arg*/) {
        std::cout << vmstate.stack.top() << std::endl;
        return true;
    });

    // TODO create instructions
    register_instruction(state, "LOAD_CONST", [](vm_state& vmstate, const item_t arg) {
        vmstate.stack.push(arg);
        return true;
    });

    register_instruction(
        state, "EXIT", [](vm_state& vmstate, const item_t /*arg*/) { return false; });

    register_instruction(state, "POP", [](vm_state& vmstate, const item_t /*arg*/) {
        vmstate.stack.pop();
        return true;
    });

    register_instruction(state, "ADD", [](vm_state& vmstate, const item_t /*arg*/) {
        item_t a = vmstate.stack.top();
        vmstate.stack.pop();
        item_t b = vmstate.stack.top();
        vmstate.stack.pop();
        vmstate.stack.push(a + b);
        return true;
    });

    register_instruction(state, "DIV", [](vm_state& vmstate, const item_t /*arg*/) {
        if (vmstate.stack.top() == 0) {
            throw div_by_zero{"div_by_zero"};
        }
        item_t a = vmstate.stack.top();
        vmstate.stack.pop();
        item_t b = vmstate.stack.top();
        vmstate.stack.pop();
        vmstate.stack.push(b / a);
        return true;
    });

    register_instruction(state, "EQ", [](vm_state& vmstate, const item_t /*arg*/) {
        item_t a = vmstate.stack.top();
        vmstate.stack.pop();
        item_t b = vmstate.stack.top();
        vmstate.stack.pop();
        if (a == b) {
            vmstate.stack.push(1);
        }
        else {
            vmstate.stack.push(0);
        }
        return true;
    });

    register_instruction(state, "NEQ", [](vm_state& vmstate, const item_t /*arg*/) {
        item_t a = vmstate.stack.top();
        vmstate.stack.pop();
        item_t b = vmstate.stack.top();
        vmstate.stack.pop();
        if (a == b) {
            vmstate.stack.push(0);
        }
        else {
            vmstate.stack.push(1);
        }
        return true;
    });

    register_instruction(state, "DUP", [](vm_state& vmstate, const item_t /*arg*/) {
        item_t a = vmstate.stack.top();
        vmstate.stack.push(a);
        return true;
    });

    register_instruction(state, "JMP", [](vm_state& vmstate, const item_t arg) {
        unsigned long size = vmstate.stack.size();
        if (arg < 0 || arg > size) {
            throw vm_segfault("vm_segfault");
        }
        vmstate.pc = arg;
        return true;
    });

    register_instruction(state, "JMPZ", [](vm_state& vmstate, const item_t arg) {
        unsigned long size = vmstate.stack.size();
        if (arg < 0 || arg > size) {
            throw vm_segfault("vm_segfault");
        }
        item_t a = vmstate.stack.top();
        vmstate.stack.pop();
        if (a == 0) {
            vmstate.pc = arg;
            return true;
        }
    });

    register_instruction(state, "WRITE", [](vm_state& vmstate, const item_t /*arg*/) {
        item_t a = vmstate.stack.top();
        vmstate.output += std::to_string(a);
        return true;
    });

    register_instruction(state, "WRITE_CHAR", [](vm_state& vmstate, const item_t /*arg*/) {
        item_t a = vmstate.stack.top();
        vmstate.output += char(a);
        return true;
    });

    return state;
}

void register_instruction(vm_state& state, std::string_view name, const op_action_t& action)
{
    size_t op_id = state.next_op_id;

    // TODO make instruction available to vm
    state.instruction_actions.insert({op_id, action});
    state.instruction_ids.insert({std::string(name), op_id});
    state.instruction_names.insert({op_id, std::string(name)});
    state.next_op_id++;
}

code_t assemble(const vm_state& state, std::string_view input_program)
{
    code_t code;

    // convert each line separately
    for (auto& line : util::split(input_program, '\n')) {

        auto line_words = util::split(line, ' ');

        // only support instruction and one argument
        if (line_words.size() >= 3) {
            throw invalid_instruction{std::string{"more than one instruction argument: "} + line};
        }

        // look up instruction id
        auto& op_name    = line_words[0];
        auto  find_op_id = state.instruction_ids.find(op_name);
        if (find_op_id == std::end(state.instruction_ids)) {
            throw invalid_instruction{std::string{"unknown instruction: "} + op_name};
        }
        op_id_t op_id = find_op_id->second;

        // parse the argument
        item_t argument{0};
        if (line_words.size() == 2) {
            // return Integer value corresponding to the content of str.
            argument = std::stoll(line_words[1]);
        }

        // and save the instruction to the code store
        code.emplace_back(op_id, argument);
    }

    return code;
}

std::tuple<item_t, std::string> run(vm_state& vm, const code_t& code)
{
    // to help you debugging the code!
    if (vm.debug) {
        std::cout << "=== running vm ======================" << std::endl;
        std::cout << "disassembly of run code:" << std::endl;
        for (const auto& [op_id, arg] : code) {
            if (not vm.instruction_names.contains(op_id)) {
                std::cout << "could not disassemble - op_id unknown..." << std::endl;
                std::cout << "turning off debug mode." << std::endl;
                vm.debug = false;
                break;
            }
            std::cout << vm.instruction_names[op_id] << " " << arg << std::endl;
        }
        std::cout << "=== end of disassembly" << std::endl << std::endl;
    }

    // execution loop for the machine
    while (true) {

        auto& [op_id, arg] = code[vm.pc];

        if (vm.debug) {
            std::cout << "-- exec " << vm.instruction_names[op_id] << " arg=" << arg
                      << " at pc=" << vm.pc << std::endl;
        }

        // increase the program counter here so its value can be overwritten
        // by the instruction when it executes!
        vm.pc += 1;

        // TODO execute instruction and stop if the action returns false.
        if (not vm.instruction_actions[op_id](vm, arg)) {
            return {vm.stack.top(), vm.output};
        }
    }

    return {vm.stack.top(), vm.output};   // TODO: return tuple(exit value, output text)
}

}   // namespace vm
