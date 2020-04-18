#ifndef PARSER_H
#define PARSER_H

#include "Scanner.h"
#include "Node.h"

/**
 * Given a Scanner, return a parse tree Node* from it.
 * Caller is responsible for calling Node_drop on returned
 * pointer.
 */
Node* parse(Scanner *s);

#endif
