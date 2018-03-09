# Tests

## Test 1
### Input:
Code1.lth
### Output:
```
TERMINAL: func
TERMINAL: identifier
TERMINAL: (
TERMINAL: identifier
Identifier_list1 -> identifier 
TERMINAL: ,
TERMINAL: identifier
Identifier_list1 -> Identifier_list1 , identifier 
Identifier_list -> Identifier_list1 
TERMINAL: )
TERMINAL: {
TERMINAL: identifier
TERMINAL: =
TERMINAL: identifier
Primary_expression -> identifier 
Postfix_expression -> Primary_expression 
Unary_expression -> Postfix_expression 
Cast_expression -> Unary_expression 
Power -> Cast_expression 
Multiplicative_expression -> Power 
TERMINAL: *
TERMINAL: identifier
Primary_expression -> identifier 
Postfix_expression -> Primary_expression 
Unary_expression -> Postfix_expression 
Cast_expression -> Unary_expression 
Power -> Cast_expression 
Multiplicative_expression -> Multiplicative_expression * Power 
Arithmetic_expression -> Multiplicative_expression 
Bitwise_expression -> Arithmetic_expression 
Relational_rest -> 
Relational_expression -> Bitwise_expression Relational_rest 
Not_expression -> Relational_expression 
And_expression -> Not_expression 
Or_expression -> And_expression 
Conditional_expression -> Or_expression 
Assignment_expression -> Conditional_expression 
Assignment_expression -> identifier = Assignment_expression 
Expression -> Assignment_expression 
TERMINAL: ;
Expression_statement -> Expression ; 
Statement -> Expression_statement 
Statements -> 
Statements -> Statement Statements 
TERMINAL: }
Block -> { Statements } 
Function_statement -> func identifier ( Identifier_list ) Block 
Function_statements -> 
Function_statements -> Function_statement Function_statements 
Program -> Function_statements 
Succesfully parsed.
```

## Test 2
### Input:
Code2.lth
### Output:
```
TERMINAL: func
TERMINAL: identifier
TERMINAL: (
TERMINAL: identifier
Identifier_list1 -> identifier 
Identifier_list -> Identifier_list1 
TERMINAL: )
TERMINAL: {
TERMINAL: return
TERMINAL: identifier
Primary_expression -> identifier 
Postfix_expression -> Primary_expression 
Unary_expression -> Postfix_expression 
Cast_expression -> Unary_expression 
Power -> Cast_expression 
Multiplicative_expression -> Power 
TERMINAL: *
TERMINAL: identifier
Primary_expression -> identifier 
Postfix_expression -> Primary_expression 
TERMINAL: (
TERMINAL: identifier
Primary_expression -> identifier 
Postfix_expression -> Primary_expression 
Unary_expression -> Postfix_expression 
Cast_expression -> Unary_expression 
Power -> Cast_expression 
Multiplicative_expression -> Power 
Arithmetic_expression -> Multiplicative_expression 
TERMINAL: -
TERMINAL: int_literal
Literals -> int_literal 
Primary_expression -> Literals 
Postfix_expression -> Primary_expression 
Unary_expression -> Postfix_expression 
Cast_expression -> Unary_expression 
Power -> Cast_expression 
Multiplicative_expression -> Power 
Arithmetic_expression -> Arithmetic_expression - Multiplicative_expression 
Bitwise_expression -> Arithmetic_expression 
Relational_rest -> 
Relational_expression -> Bitwise_expression Relational_rest 
Not_expression -> Relational_expression 
And_expression -> Not_expression 
Or_expression -> And_expression 
Conditional_expression -> Or_expression 
Assignment_expression -> Conditional_expression 
Expression -> Assignment_expression 
Expression_list -> Expression 
TERMINAL: )
Postfix_expression -> Postfix_expression ( Expression_list ) 
Unary_expression -> Postfix_expression 
Cast_expression -> Unary_expression 
Power -> Cast_expression 
Multiplicative_expression -> Multiplicative_expression * Power 
Arithmetic_expression -> Multiplicative_expression 
Bitwise_expression -> Arithmetic_expression 
Relational_rest -> 
Relational_expression -> Bitwise_expression Relational_rest 
Not_expression -> Relational_expression 
And_expression -> Not_expression 
Or_expression -> And_expression 
Conditional_expression -> Or_expression 
Assignment_expression -> Conditional_expression 
Expression -> Assignment_expression 
TERMINAL: ;
Return_statement -> return Expression ; 
Statement -> Return_statement 
Statements -> 
Statements -> Statement Statements 
TERMINAL: }
Block -> { Statements } 
Function_statement -> func identifier ( Identifier_list ) Block 
TERMINAL: func
TERMINAL: identifier
TERMINAL: (
TERMINAL: identifier
Identifier_list1 -> identifier 
Identifier_list -> Identifier_list1 
TERMINAL: )
TERMINAL: {
TERMINAL: if
TERMINAL: (
TERMINAL: identifier
Primary_expression -> identifier 
Postfix_expression -> Primary_expression 
Unary_expression -> Postfix_expression 
Cast_expression -> Unary_expression 
Power -> Cast_expression 
Multiplicative_expression -> Power 
Arithmetic_expression -> Multiplicative_expression 
Bitwise_expression -> Arithmetic_expression 
TERMINAL: ==
Relational_op -> == 
TERMINAL: int_literal
Literals -> int_literal 
Primary_expression -> Literals 
Postfix_expression -> Primary_expression 
Unary_expression -> Postfix_expression 
Cast_expression -> Unary_expression 
Power -> Cast_expression 
Multiplicative_expression -> Power 
Arithmetic_expression -> Multiplicative_expression 
Bitwise_expression -> Arithmetic_expression 
Relational_rest -> Relational_op Bitwise_expression 
Relational_expression -> Bitwise_expression Relational_rest 
Not_expression -> Relational_expression 
And_expression -> Not_expression 
Or_expression -> And_expression 
Conditional_expression -> Or_expression 
TERMINAL: )
TERMINAL: {
TERMINAL: return
TERMINAL: int_literal
Literals -> int_literal 
Primary_expression -> Literals 
Postfix_expression -> Primary_expression 
Unary_expression -> Postfix_expression 
Cast_expression -> Unary_expression 
Power -> Cast_expression 
Multiplicative_expression -> Power 
Arithmetic_expression -> Multiplicative_expression 
Bitwise_expression -> Arithmetic_expression 
Relational_rest -> 
Relational_expression -> Bitwise_expression Relational_rest 
Not_expression -> Relational_expression 
And_expression -> Not_expression 
Or_expression -> And_expression 
Conditional_expression -> Or_expression 
Assignment_expression -> Conditional_expression 
Expression -> Assignment_expression 
TERMINAL: ;
Return_statement -> return Expression ; 
Statement -> Return_statement 
Statements -> 
Statements -> Statement Statements 
TERMINAL: }
Block -> { Statements } 
TERMINAL: else
TERMINAL: {
TERMINAL: if
TERMINAL: (
TERMINAL: identifier
Primary_expression -> identifier 
Postfix_expression -> Primary_expression 
Unary_expression -> Postfix_expression 
Cast_expression -> Unary_expression 
Power -> Cast_expression 
Multiplicative_expression -> Power 
Arithmetic_expression -> Multiplicative_expression 
Bitwise_expression -> Arithmetic_expression 
TERMINAL: ==
Relational_op -> == 
TERMINAL: int_literal
Literals -> int_literal 
Primary_expression -> Literals 
Postfix_expression -> Primary_expression 
Unary_expression -> Postfix_expression 
Cast_expression -> Unary_expression 
Power -> Cast_expression 
Multiplicative_expression -> Power 
Arithmetic_expression -> Multiplicative_expression 
Bitwise_expression -> Arithmetic_expression 
Relational_rest -> Relational_op Bitwise_expression 
Relational_expression -> Bitwise_expression Relational_rest 
Not_expression -> Relational_expression 
And_expression -> Not_expression 
Or_expression -> And_expression 
Conditional_expression -> Or_expression 
TERMINAL: )
TERMINAL: {
TERMINAL: return
TERMINAL: int_literal
Literals -> int_literal 
Primary_expression -> Literals 
Postfix_expression -> Primary_expression 
Unary_expression -> Postfix_expression 
Cast_expression -> Unary_expression 
Power -> Cast_expression 
Multiplicative_expression -> Power 
Arithmetic_expression -> Multiplicative_expression 
Bitwise_expression -> Arithmetic_expression 
Relational_rest -> 
Relational_expression -> Bitwise_expression Relational_rest 
Not_expression -> Relational_expression 
And_expression -> Not_expression 
Or_expression -> And_expression 
Conditional_expression -> Or_expression 
Assignment_expression -> Conditional_expression 
Expression -> Assignment_expression 
TERMINAL: ;
Return_statement -> return Expression ; 
Statement -> Return_statement 
Statements -> 
Statements -> Statement Statements 
TERMINAL: }
Block -> { Statements } 
TERMINAL: else
TERMINAL: {
TERMINAL: return
TERMINAL: identifier
Primary_expression -> identifier 
Postfix_expression -> Primary_expression 
TERMINAL: (
TERMINAL: identifier
Primary_expression -> identifier 
Postfix_expression -> Primary_expression 
Unary_expression -> Postfix_expression 
Cast_expression -> Unary_expression 
Power -> Cast_expression 
Multiplicative_expression -> Power 
Arithmetic_expression -> Multiplicative_expression 
TERMINAL: -
TERMINAL: int_literal
Literals -> int_literal 
Primary_expression -> Literals 
Postfix_expression -> Primary_expression 
Unary_expression -> Postfix_expression 
Cast_expression -> Unary_expression 
Power -> Cast_expression 
Multiplicative_expression -> Power 
Arithmetic_expression -> Arithmetic_expression - Multiplicative_expression 
Bitwise_expression -> Arithmetic_expression 
Relational_rest -> 
Relational_expression -> Bitwise_expression Relational_rest 
Not_expression -> Relational_expression 
And_expression -> Not_expression 
Or_expression -> And_expression 
Conditional_expression -> Or_expression 
Assignment_expression -> Conditional_expression 
Expression -> Assignment_expression 
Expression_list -> Expression 
TERMINAL: )
Postfix_expression -> Postfix_expression ( Expression_list ) 
Unary_expression -> Postfix_expression 
Cast_expression -> Unary_expression 
Power -> Cast_expression 
Multiplicative_expression -> Power 
Arithmetic_expression -> Multiplicative_expression 
TERMINAL: +
TERMINAL: identifier
Primary_expression -> identifier 
Postfix_expression -> Primary_expression 
TERMINAL: (
TERMINAL: identifier
Primary_expression -> identifier 
Postfix_expression -> Primary_expression 
Unary_expression -> Postfix_expression 
Cast_expression -> Unary_expression 
Power -> Cast_expression 
Multiplicative_expression -> Power 
Arithmetic_expression -> Multiplicative_expression 
TERMINAL: -
TERMINAL: int_literal
Literals -> int_literal 
Primary_expression -> Literals 
Postfix_expression -> Primary_expression 
Unary_expression -> Postfix_expression 
Cast_expression -> Unary_expression 
Power -> Cast_expression 
Multiplicative_expression -> Power 
Arithmetic_expression -> Arithmetic_expression - Multiplicative_expression 
Bitwise_expression -> Arithmetic_expression 
Relational_rest -> 
Relational_expression -> Bitwise_expression Relational_rest 
Not_expression -> Relational_expression 
And_expression -> Not_expression 
Or_expression -> And_expression 
Conditional_expression -> Or_expression 
Assignment_expression -> Conditional_expression 
Expression -> Assignment_expression 
Expression_list -> Expression 
TERMINAL: )
Postfix_expression -> Postfix_expression ( Expression_list ) 
Unary_expression -> Postfix_expression 
Cast_expression -> Unary_expression 
Power -> Cast_expression 
Multiplicative_expression -> Power 
Arithmetic_expression -> Arithmetic_expression + Multiplicative_expression 
Bitwise_expression -> Arithmetic_expression 
Relational_rest -> 
Relational_expression -> Bitwise_expression Relational_rest 
Not_expression -> Relational_expression 
And_expression -> Not_expression 
Or_expression -> And_expression 
Conditional_expression -> Or_expression 
Assignment_expression -> Conditional_expression 
Expression -> Assignment_expression 
TERMINAL: ;
Return_statement -> return Expression ; 
Statement -> Return_statement 
Statements -> 
Statements -> Statement Statements 
TERMINAL: }
Block -> { Statements } 
If_rest -> else Block 
If_statement -> if ( Conditional_expression ) Block If_rest 
Statement -> If_statement 
Statements -> 
Statements -> Statement Statements 
TERMINAL: }
Block -> { Statements } 
If_rest -> else Block 
If_statement -> if ( Conditional_expression ) Block If_rest 
Statement -> If_statement 
Statements -> 
Statements -> Statement Statements 
TERMINAL: }
Block -> { Statements } 
Function_statement -> func identifier ( Identifier_list ) Block 
Function_statements -> 
Function_statements -> Function_statement Function_statements 
Function_statements -> Function_statement Function_statements 
Program -> Function_statements 
Succesfully parsed.
```

## Test 3
### Input:
Code3.lth
### Output:
```
TERMINAL: func
TERMINAL: identifier
TERMINAL: (
TERMINAL: identifier
Identifier_list1 -> identifier 
TERMINAL: ,
TERMINAL: identifier
Identifier_list1 -> Identifier_list1 , identifier 
Identifier_list -> Identifier_list1 
TERMINAL: )
TERMINAL: {
TERMINAL: identifier
Primary_expression -> identifier 
Postfix_expression -> Primary_expression 
Unary_expression -> Postfix_expression 
Cast_expression -> Unary_expression 
Power -> Cast_expression 
Multiplicative_expression -> Power 
Arithmetic_expression -> Multiplicative_expression 
Bitwise_expression -> Arithmetic_expression 
Relational_rest -> 
Relational_expression -> Bitwise_expression Relational_rest 
Not_expression -> Relational_expression 
And_expression -> Not_expression 
Or_expression -> And_expression 
Conditional_expression -> Or_expression 
Assignment_expression -> Conditional_expression 
Expression -> Assignment_expression 
TERMINAL: ;
Expression_statement -> Expression ; 
Statement -> Expression_statement 
TERMINAL: identifier
TERMINAL: =
TERMINAL: int_literal
Literals -> int_literal 
Primary_expression -> Literals 
Postfix_expression -> Primary_expression 
Unary_expression -> Postfix_expression 
Cast_expression -> Unary_expression 
Power -> Cast_expression 
Multiplicative_expression -> Power 
Arithmetic_expression -> Multiplicative_expression 
Bitwise_expression -> Arithmetic_expression 
Relational_rest -> 
Relational_expression -> Bitwise_expression Relational_rest 
Not_expression -> Relational_expression 
And_expression -> Not_expression 
Or_expression -> And_expression 
Conditional_expression -> Or_expression 
Assignment_expression -> Conditional_expression 
Assignment_expression -> identifier = Assignment_expression 
Expression -> Assignment_expression 
TERMINAL: ;
Expression_statement -> Expression ; 
Statement -> Expression_statement 
TERMINAL: for
TERMINAL: (
TERMINAL: identifier
TERMINAL: =
TERMINAL: int_literal
Literals -> int_literal 
Primary_expression -> Literals 
Postfix_expression -> Primary_expression 
Unary_expression -> Postfix_expression 
Cast_expression -> Unary_expression 
Power -> Cast_expression 
Multiplicative_expression -> Power 
Arithmetic_expression -> Multiplicative_expression 
Bitwise_expression -> Arithmetic_expression 
Relational_rest -> 
Relational_expression -> Bitwise_expression Relational_rest 
Not_expression -> Relational_expression 
And_expression -> Not_expression 
Or_expression -> And_expression 
Conditional_expression -> Or_expression 
Assignment_expression -> Conditional_expression 
Assignment_expression -> identifier = Assignment_expression 
Expression -> Assignment_expression 
Expression_list -> Expression 
TERMINAL: ;
TERMINAL: identifier
Primary_expression -> identifier 
Postfix_expression -> Primary_expression 
Unary_expression -> Postfix_expression 
Cast_expression -> Unary_expression 
Power -> Cast_expression 
Multiplicative_expression -> Power 
Arithmetic_expression -> Multiplicative_expression 
Bitwise_expression -> Arithmetic_expression 
TERMINAL: <
Relational_op -> < 
TERMINAL: identifier
Primary_expression -> identifier 
Postfix_expression -> Primary_expression 
Unary_expression -> Postfix_expression 
Cast_expression -> Unary_expression 
Power -> Cast_expression 
Multiplicative_expression -> Power 
Arithmetic_expression -> Multiplicative_expression 
Bitwise_expression -> Arithmetic_expression 
Relational_rest -> Relational_op Bitwise_expression 
Relational_expression -> Bitwise_expression Relational_rest 
Not_expression -> Relational_expression 
And_expression -> Not_expression 
Or_expression -> And_expression 
Conditional_expression -> Or_expression 
For_condition -> Conditional_expression 
TERMINAL: ;
TERMINAL: identifier
Primary_expression -> identifier 
Postfix_expression -> Primary_expression 
TERMINAL: ++
Postfix_expression -> Postfix_expression ++ 
Unary_expression -> Postfix_expression 
Cast_expression -> Unary_expression 
Power -> Cast_expression 
Multiplicative_expression -> Power 
Arithmetic_expression -> Multiplicative_expression 
Bitwise_expression -> Arithmetic_expression 
Relational_rest -> 
Relational_expression -> Bitwise_expression Relational_rest 
Not_expression -> Relational_expression 
And_expression -> Not_expression 
Or_expression -> And_expression 
Conditional_expression -> Or_expression 
Assignment_expression -> Conditional_expression 
Expression -> Assignment_expression 
Expression_list -> Expression 
TERMINAL: )
TERMINAL: {
TERMINAL: identifier
TERMINAL: =
TERMINAL: identifier
Primary_expression -> identifier 
Postfix_expression -> Primary_expression 
Unary_expression -> Postfix_expression 
Cast_expression -> Unary_expression 
Power -> Cast_expression 
Multiplicative_expression -> Power 
Arithmetic_expression -> Multiplicative_expression 
TERMINAL: +
TERMINAL: identifier
Primary_expression -> identifier 
Postfix_expression -> Primary_expression 
TERMINAL: [
TERMINAL: identifier
Primary_expression -> identifier 
Postfix_expression -> Primary_expression 
Unary_expression -> Postfix_expression 
Cast_expression -> Unary_expression 
Power -> Cast_expression 
Multiplicative_expression -> Power 
Arithmetic_expression -> Multiplicative_expression 
Bitwise_expression -> Arithmetic_expression 
TERMINAL: ]
Postfix_expression -> Postfix_expression [ Bitwise_expression ] 
Unary_expression -> Postfix_expression 
Cast_expression -> Unary_expression 
Power -> Cast_expression 
Multiplicative_expression -> Power 
Arithmetic_expression -> Arithmetic_expression + Multiplicative_expression 
Bitwise_expression -> Arithmetic_expression 
Relational_rest -> 
Relational_expression -> Bitwise_expression Relational_rest 
Not_expression -> Relational_expression 
And_expression -> Not_expression 
Or_expression -> And_expression 
Conditional_expression -> Or_expression 
Assignment_expression -> Conditional_expression 
Assignment_expression -> identifier = Assignment_expression 
Expression -> Assignment_expression 
TERMINAL: ;
Expression_statement -> Expression ; 
Statement -> Expression_statement 
Statements -> 
Statements -> Statement Statements 
TERMINAL: }
Block -> { Statements } 
For_statement -> for ( Expression_list ; For_condition ; Expression_list ) Block 
Statement -> For_statement 
TERMINAL: return
TERMINAL: identifier
Primary_expression -> identifier 
Postfix_expression -> Primary_expression 
Unary_expression -> Postfix_expression 
Cast_expression -> Unary_expression 
Power -> Cast_expression 
Multiplicative_expression -> Power 
TERMINAL: /
TERMINAL: (
TERMINAL: float
Type -> float 
TERMINAL: )
TERMINAL: identifier
Primary_expression -> identifier 
Postfix_expression -> Primary_expression 
Unary_expression -> Postfix_expression 
Cast_expression -> Unary_expression 
Cast_expression -> ( Type ) Cast_expression 
Power -> Cast_expression 
Multiplicative_expression -> Multiplicative_expression / Power 
Arithmetic_expression -> Multiplicative_expression 
Bitwise_expression -> Arithmetic_expression 
Relational_rest -> 
Relational_expression -> Bitwise_expression Relational_rest 
Not_expression -> Relational_expression 
And_expression -> Not_expression 
Or_expression -> And_expression 
Conditional_expression -> Or_expression 
Assignment_expression -> Conditional_expression 
Expression -> Assignment_expression 
TERMINAL: ;
Return_statement -> return Expression ; 
Statement -> Return_statement 
Statements -> 
Statements -> Statement Statements 
Statements -> Statement Statements 
Statements -> Statement Statements 
Statements -> Statement Statements 
TERMINAL: }
Block -> { Statements } 
Function_statement -> func identifier ( Identifier_list ) Block 
Function_statements -> 
Function_statements -> Function_statement Function_statements 
Program -> Function_statements 
Succesfully parsed.
```