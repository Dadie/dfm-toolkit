# DFM Lexer

A given DFM file's content is cut into tokens using the following NFA automata by seeking the longest match.

## **Comment Token**
![NFA automaton for dfm comment tokens](token_matcher_comment.svg)

## **Float Token**
![NFA automaton for dfm float tokens](token_matcher_float.svg)

## **Float Datetime Token**
![NFA automaton for dfm float datetime tokens](token_matcher_float_datetime.svg)

## **Integer Datetime Token**
![NFA automaton for dfm float datetime tokens](token_matcher_integer_datetime.svg)

## **Hex Number Token**
![NFA automaton for dfm hex number tokens](token_matcher_hex.svg)

## **Integer Token**
![NFA automaton for dfm hex number tokens](token_matcher_integer.svg)

## **Word Token**
![NFA automaton for dfm work tokens](token_matcher_non_special.svg)

## **String Token**
![NFA automaton for dfm string tokens](token_matcher_string.svg)

## **String Character Token**
![NFA automaton for dfm string character tokens](token_matcher_string_char.svg)

## **Special Character Token**
![NFA automaton for dfm special character tokens](token_matcher_token.svg)
