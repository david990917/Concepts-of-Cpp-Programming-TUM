#include "validator.h"

#include <variant>
#include <vector>

#include "token.h"

namespace sql {

struct TransitionFromStartVisitor
{
    /// Only the `Select` token advances the FSM from the `Start` state
    /// TODO: Correct the behaviour
    State operator()(token::Select) const { return state::SelectStmt{}; }

    /// All the other tokens, put it in the invalid state
    State operator()(token::From) const { return state::Invalid{}; }
    State operator()(token::Comma) const { return state::Invalid{}; }
    State operator()(token::Asterisks) const { return state::Invalid{}; }
    State operator()(token::Semicolon) const { return state::Invalid{}; }
    State operator()(token::Identifier) const { return state::Invalid{}; }
};

// New added
struct TransitionFromSelectStmtVisitor
{
    State operator()(token::Select) const { return state::Invalid{}; }
    State operator()(token::From) const { return state::Invalid{}; }
    State operator()(token::Comma) const { return state::Invalid{}; }
    State operator()(token::Asterisks) const { return state::AllColumns{}; }
    State operator()(token::Semicolon) const { return state::Invalid{}; }
    State operator()(token::Identifier) const { return state::NamedColumn{}; }
};
struct TransitionFromAllColumnsVisitor
{
    State operator()(token::Select) const { return state::Invalid{}; }
    State operator()(token::From) const { return state::FromClause{}; }
    State operator()(token::Comma) const { return state::Invalid{}; }
    State operator()(token::Asterisks) const { return state::Invalid{}; }
    State operator()(token::Semicolon) const { return state::Invalid{}; }
    State operator()(token::Identifier) const { return state::Invalid{}; }
};
struct TransitionFromNamedColumnVisitor
{
    State operator()(token::Select) const { return state::Invalid{}; }
    State operator()(token::From) const { return state::FromClause{}; }
    State operator()(token::Comma) const { return state::MoreColumns{}; }
    State operator()(token::Asterisks) const { return state::Invalid{}; }
    State operator()(token::Semicolon) const { return state::Invalid{}; }
    State operator()(token::Identifier) const { return state::Invalid{}; }
};
struct TransitionFromMoreColumnsVisitor
{
    State operator()(token::Select) const { return state::Invalid{}; }
    State operator()(token::From) const { return state::Invalid{}; }
    State operator()(token::Comma) const { return state::Invalid{}; }
    State operator()(token::Asterisks) const { return state::Invalid{}; }
    State operator()(token::Semicolon) const { return state::Invalid{}; }
    State operator()(token::Identifier) const { return state::NamedColumn{}; }
};
struct TransitionFromFromClauseVisitor
{
    State operator()(token::Select) const { return state::Invalid{}; }
    State operator()(token::From) const { return state::Invalid{}; }
    State operator()(token::Comma) const { return state::Invalid{}; }
    State operator()(token::Asterisks) const { return state::Valid{}; }
    State operator()(token::Semicolon) const { return state::Valid{}; }
    State operator()(token::Identifier) const { return state::TableName{}; }
};
struct TransitionFromTableNameVisitor
{
    State operator()(token::Select) const { return state::Invalid{}; }
    State operator()(token::From) const { return state::Invalid{}; }
    State operator()(token::Comma) const { return state::Invalid{}; }
    State operator()(token::Asterisks) const { return state::Invalid{}; }
    State operator()(token::Semicolon) const { return state::Valid{}; }
    State operator()(token::Identifier) const { return state::Invalid{}; }
};
struct TransitionFromValidVisitor
{
    State operator()(token::Select) const { return state::Invalid{}; }
    State operator()(token::From) const { return state::Invalid{}; }
    State operator()(token::Comma) const { return state::Invalid{}; }
    State operator()(token::Asterisks) const { return state::Invalid{}; }
    State operator()(token::Semicolon) const { return state::Valid{}; }
    State operator()(token::Identifier) const { return state::Invalid{}; }
};
struct TransitionFromInvalidVisitor
{
    State operator()(token::Select) const { return state::Invalid{}; }
    State operator()(token::From) const { return state::Invalid{}; }
    State operator()(token::Comma) const { return state::Invalid{}; }
    State operator()(token::Asterisks) const { return state::Invalid{}; }
    State operator()(token::Semicolon) const { return state::Invalid{}; }
    State operator()(token::Identifier) const { return state::Invalid{}; }
};


State transition(state::Start, Token token)
{
    return std::visit(TransitionFromStartVisitor{}, token.value());
}
// New Added
State transition(state::SelectStmt, Token token)
{
    return std::visit(TransitionFromSelectStmtVisitor{}, token.value());
}
State transition(state::AllColumns, Token token)
{
    return std::visit(TransitionFromAllColumnsVisitor{}, token.value());
}
State transition(state::NamedColumn, Token token)
{
    return std::visit(TransitionFromNamedColumnVisitor{}, token.value());
}
State transition(state::MoreColumns, Token token)
{
    return std::visit(TransitionFromMoreColumnsVisitor{}, token.value());
}
State transition(state::FromClause, Token token)
{
    return std::visit(TransitionFromFromClauseVisitor{}, token.value());
}
State transition(state::TableName, Token token)
{
    return std::visit(TransitionFromTableNameVisitor{}, token.value());
}
State transition(state::Valid, Token token)
{
    // TODO: Implement
    return std::visit(TransitionFromValidVisitor{}, token.value());
}
State transition(state::Invalid, Token token)
{
    // TODO: Implement
    return std::visit(TransitionFromInvalidVisitor{}, token.value());
}


bool SqlValidator::is_valid() const
{
    /// TODO: Implement this
    if (std::holds_alternative<state::Invalid>(state_)) {
        return false;
    }
    return true;
}

void SqlValidator::handle(Token token)
{
    /// TODO: Implement this
    if (std::holds_alternative<state::Start>(state_)) {
        state_ = transition(state::Start{}, token);
    }
    else if (std::holds_alternative<state::Invalid>(state_)) {
        state_ = transition(state::Invalid{}, token);
    }
    else if (std::holds_alternative<state::Valid>(state_)) {
        state_ = transition(state::Valid{}, token);
    }
    else if (std::holds_alternative<state::SelectStmt>(state_)) {
        state_ = transition(state::SelectStmt{}, token);
    }
    else if (std::holds_alternative<state::NamedColumn>(state_)) {
        state_ = transition(state::NamedColumn{}, token);
    }
    else if (std::holds_alternative<state::AllColumns>(state_)) {
        state_ = transition(state::AllColumns{}, token);
    }
    else if (std::holds_alternative<state::FromClause>(state_)) {
        state_ = transition(state::FromClause{}, token);
    }
    else if (std::holds_alternative<state::MoreColumns>(state_)) {
        state_ = transition(state::MoreColumns{}, token);
    }
    else if (std::holds_alternative<state::TableName>(state_)) {
        state_ = transition(state::TableName{}, token);
    }
}

bool is_valid_sql_query(std::vector<Token> tokens)
{
    SqlValidator validator;
    for (auto& token : tokens) {
        validator.handle(token);
        if (!validator.is_valid()) {
            return false;
        }
    }
    return true;
}

}   // namespace sql
