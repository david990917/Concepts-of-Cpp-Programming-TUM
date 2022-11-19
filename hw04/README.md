# hw04 

- throw exception
- `[](){} lambda function`
- corner case

----

1. Implement the lambda function

```cpp
register_instruction(state, "JMPZ", [](vm_state& vmstate, const item_t arg) {
    if (vmstate.stack.size() == 0) {
        throw vm_stackfail("vm_stackfail");
    }

    if (arg < 0 || arg >= vmstate.codesize) {
        std::cout << arg << " "
                    << "codesize: " << vmstate.codesize << std::endl;
        throw vm_segfault("vm_segfault");
    }
    item_t a = vmstate.stack.top();
    vmstate.stack.pop();
    if (a == 0) {
        vmstate.pc = arg;
    }
    return true;
});
```

1. register functions


```cpp
void register_instruction(vm_state& state, std::string_view name, const op_action_t& action)
{
    size_t op_id = state.next_op_id;

    // TODO make instruction available to vm
    state.instruction_actions.insert({op_id, action});
    state.instruction_ids.insert({std::string(name), op_id});
    state.instruction_names.insert({op_id, std::string(name)});
    state.next_op_id++;
}
```

3. execute these functions

```cpp
if (not vm.instruction_actions[op_id](vm, arg)) {
    return {vm.stack.top(), vm.output};
}
```




