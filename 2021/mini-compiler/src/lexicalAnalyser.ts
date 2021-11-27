import { tokenType, tokenPattern } from './grammar';

export const TOKEN_ERROR = 'TOKEN_ERROR';
// can be expanded to check for EOL, or other delimiter character
const delimiter = /^[\s;\-_\\\/]+/;

export interface Token {
    lexeme: string;
    type: tokenType | string;
    position: [number, number];
}

const tokenize = (input: string, i: number): [Token, number] => {
    // get the string from the index
    const str = input.slice(i);

    // use delimiter regex to get rid of whitespace/separators
    const trimmed = str.match(delimiter);
    const trimmedLength = trimmed ? trimmed[0].length : 0;

    let result: Token | null = null;
    let testStr = str.slice(trimmedLength);
    for (const regex in tokenPattern) {
        // test regex with the string, if matched then get substring of the match
        if (tokenPattern[regex].test(testStr)) {
            result = {
                lexeme: testStr.match(tokenPattern[regex])![0],
                type: regex,
                position: [i + trimmedLength, i + trimmedLength + testStr.length - 1],
            };
            break;
        }
    }

    // return the token and the index jump
    if (result) {
        return [result, i + result.lexeme.length + trimmedLength];
    }

    throw `LexicalError: unrecognised token [${i + trimmedLength},${
        i + trimmedLength + testStr.length - 1
    }] "${testStr}"`;
};

export const scanner = (input: string): Token[] => {
    const output: Token[] = [];

    // remove unnecessary whitespace
    input = input.trim();

    // scan through input
    for (let i = 0, len = input.length; i < len; ) {
        let result = tokenize(input, i);
        let token = result[0];
        i = result[1];
        output.push(token);
    }

    return output;
};
