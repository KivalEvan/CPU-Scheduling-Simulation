import { tokenType } from './grammar';
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

    try {
        const acceptToken = (node: ASTNode, type: tokenType) => {
            if (tokens[currentToken].type === type) {
                node.params!.push({
                    type: tokens[currentToken].type,
                    value: tokens[currentToken].lexeme,
                });
                currentToken++;
            } else {
                parseError();
            }
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
            switch (tokens[currentToken]?.type) {
                case 'CAT_TALK': {
                    acceptToken(node, 'CAT_TALK');
                    parseCatTalkPrime(node);
                    return;
                }
                case undefined: {
                    return;
                }
                default: {
                    parseError();
                }
            }
        };
        const parseCatTalkPrime = (node: ASTNode) => {
            switch (tokens[currentToken]?.type) {
                case 'CAT_TALK': {
                    parseCatTalk(node);
                    return;
                }
                case undefined: {
                    return;
                }
                default: {
                    parseError();
                }
            }
        };
        const parseCatPurr = (node: ASTNode) => {
            switch (tokens[currentToken]?.type) {
                case 'CAT_PURR': {
                    acceptToken(node, 'CAT_PURR');
                    parseCatTalk(node);
                    return;
                }
                case undefined: {
                    return;
                }
                default: {
                    parseError();
                }
            }
        };
        const parseCatHiss = (node: ASTNode) => {
            switch (tokens[currentToken]?.type) {
                case 'CAT_HISS': {
                    acceptToken(node, 'CAT_HISS');
                    parseCatTalk(node);
                    return;
                }
                case undefined: {
                    return;
                }
                default: {
                    parseError();
                }
            }
        };
        const parseCatMimic = (node: ASTNode) => {
            switch (tokens[currentToken]?.type) {
                case 'CAT_MIMIC': {
                    acceptToken(node, 'CAT_MIMIC');
                    return;
                }
                case undefined: {
                    return;
                }
                default: {
                    parseError();
                }
            }
        };
        const parseError = () => {
            if (currentToken >= tokens.length) {
                throw `missing next token`;
            }
            throw `unexpected token [${tokens[currentToken].position[0]},${tokens[currentToken].position[1]}]: ${tokens[currentToken].type}:${tokens[currentToken].lexeme}`;
        };

        parseCatSpeak();
    } catch (e) {
        throw `SyntaxError: ${e}`;
    }

    return ast;
};
