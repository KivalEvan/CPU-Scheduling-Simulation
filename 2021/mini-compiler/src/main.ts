import './style.css';

import { scanner } from './lexicalAnalyser';
import { parser, AbstractSyntaxTree } from './syntaxAnalyser';

const htmlInputTextArea = document.querySelector<HTMLTextAreaElement>('#input-text')!;
const htmlOutputLexerTextArea =
    document.querySelector<HTMLTextAreaElement>('#output-lexer')!;
const htmlOutputSyntaxTextArea =
    document.querySelector<HTMLTextAreaElement>('#output-syntax')!;
const htmlOutputResultTextArea =
    document.querySelector<HTMLTextAreaElement>('#output-result')!;
const htmlCompileMessage = document.querySelector<HTMLSpanElement>('#compile-message')!;
const htmlCompileTimeText = document.querySelector<HTMLSpanElement>('#compile-time')!;

const getInput = () => {
    return htmlInputTextArea.value;
};

const setLexerOutput = (output: String[]) => {
    htmlOutputLexerTextArea.value = output.join('\n');
};

const setSyntaxOutput = (output: AbstractSyntaxTree) => {
    htmlOutputSyntaxTextArea.value = output.nodes
        .map((n) => n.params)
        .flat()
        .map((n) => JSON.stringify(n))
        .join('\n');
};

const setResultOutput = (output: AbstractSyntaxTree) => {
    htmlOutputResultTextArea.value = JSON.stringify(output, null, 4);
};

const onTextInput = () => {
    htmlOutputLexerTextArea.value = '';
    htmlOutputSyntaxTextArea.value = '';
    htmlOutputResultTextArea.value = '';
    htmlCompileMessage.textContent = '';
    let startTime = performance.now();
    try {
        const token = scanner(getInput());
        setLexerOutput(token.map((t) => `${t.type}:${t.lexeme}`));
        const ast = parser(token);
        setSyntaxOutput(ast);
        setResultOutput(ast);
    } catch (e) {
        if (typeof e === 'string') {
            htmlCompileMessage.textContent = e;
        }
    } finally {
        let compileTime = performance.now() - startTime;
        htmlCompileTimeText.textContent = (
            Math.round(compileTime * 10) / 10
        ).toString();
    }
};

htmlInputTextArea.addEventListener('input', onTextInput);
htmlInputTextArea.addEventListener('change', onTextInput);
