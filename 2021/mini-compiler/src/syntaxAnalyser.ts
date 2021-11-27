import { Token } from './lexicalAnalyser';

export interface AbstractSyntaxTree {
    type: string;
    nodes: ASTNode[];
}
interface ASTNode {
    type: string;
    value: string;
    params?: ASTNode[];
}

export const parser = (tokens: Token[]) => {
    let currentToken = 0;
    const ast: AbstractSyntaxTree = {
        type: 'PROGRAM',
        nodes: [],
    };

    const acceptToken = (node: ASTNode, token: Token) => {
        node.params!.push({
            type: token.type,
            value: token.lexeme,
        });
        return;
    };
    const parseCatSpeak = () => {
        const speech: ASTNode = {
            type: 'CAT_SPEAK',
            value: 'speech',
            params: [],
        };
        switch (tokens[currentToken].type) {
            case 'CAT_TALK': {
                parseCatTalk(speech);
                break;
            }
            case 'CAT_PURR': {
                parseCatPurr(speech);
                break;
            }
            case 'CAT_HISS': {
                parseCatHiss(speech);
                break;
            }
            case 'CAT_MIMIC': {
                parseCatMimic(speech);
                break;
            }
            default: {
                parseError();
            }
        }
        ast.nodes.push(speech);
    };
    const parseCatTalk = (node: ASTNode) => {
        acceptToken(node, tokens[currentToken]);
        if (!tokens[++currentToken]?.type) {
            return;
        }
        switch (tokens[currentToken].type) {
            case 'CAT_TALK': {
                parseCatTalk(node);
                if (!tokens[currentToken]?.type) {
                    return;
                }
                parseCatTalkPrime(node);
                return;
            }
            default: {
                parseError();
            }
        }
    };
    const parseCatTalkPrime = (node: ASTNode) => {
        acceptToken(node, tokens[currentToken]);
        if (!tokens[++currentToken]?.type) {
            return;
        }
        switch (tokens[currentToken].type) {
            case 'CAT_TALK': {
                parseCatTalkPrime(node);
            }
            default: {
                return;
            }
        }
    };
    const parseCatPurr = (node: ASTNode) => {
        acceptToken(node, tokens[currentToken]);
        if (!tokens[++currentToken]?.type) {
            return;
        }
        switch (tokens[currentToken].type) {
            case 'CAT_TALK': {
                parseCatTalk(node);
                return;
            }
            default: {
                parseError();
            }
        }
    };
    const parseCatHiss = (node: ASTNode) => {
        acceptToken(node, tokens[currentToken]);
        if (!tokens[++currentToken]?.type) {
            return;
        }
        switch (tokens[currentToken].type) {
            case 'CAT_TALK': {
                parseCatTalk(node);
                return;
            }
            default: {
                parseError();
            }
        }
    };
    const parseCatMimic = (node: ASTNode) => {
        acceptToken(node, tokens[currentToken]);
        if (!tokens[++currentToken]?.type) {
            return;
        }
        switch (tokens[currentToken].type) {
            default: {
                parseError();
            }
        }
    };
    const parseError = () => {
        if (currentToken >= tokens.length) {
            throw `SyntaxError: missing next token`;
        }
        throw `SyntaxError: unexpected token [${tokens[currentToken].position[0]},${tokens[currentToken].position[1]}]: ${tokens[currentToken].type}:${tokens[currentToken].lexeme}`;
    };

    parseCatSpeak();

    return ast;
};
