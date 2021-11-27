/*
CONTEXT-FREE GRAMMAR
T = { m{e}[{o}]w, p[u]r{r}, h[i]s{s}, {ke} }
N = { <CAT_SPEAK>, <CAT_TALK>, <CAT_PURR>, <CAT_HISS>, <CAT_MIMIC> }
S = { <CAT_SPEAK> }
P = { <CAT_SPEAK> -> <CAT_TALK> | <CAT_PURR> | <CAT_HISS> | <CAT_MIMIC>
      <CAT_TALK> -> m{e}[{o}]w | m{e}[{o}]w <CAT_TALK>
      <CAT_PURR> -> p[u]r{r} | p[u]r{r} <CAT_TALK>
      <CAT_HISS> -> h[i]s{s} | h[i]s{s} <CAT_TALK>
      <CAT_MIMIC> -> {ke} }


CAT LANGUAGE LEXICAL GRAMMAR IN EBNF
CAT_SPEAK ::= CAT_TALK | CAT_PURR | CAT_HISS | CAT_MIMIC
CAT_TALK ::= m{e}[{o}]w | m{e}[{o}]w CAT_TALK
CAT_PURR ::= p[u]r{r} | p[u]r{r} CAT_TALK
CAT_HISS ::= h[i]s{s} | h[i]s{s} CAT_TALK
CAT_MIMIC ::= {ke}


TOP-DOWN PARSING
LEFT-FACTORING
CAT_SPEAK ::= CAT_TALK | CAT_PURR | CAT_HISS | CAT_MIMIC
CAT_TALK ::= m{e}[{o}]w | m{e}[{o}]w CAT_TALK'
CAT_TALK' ::= CAT_TALK | ɛ
CAT_PURR ::= p[u]r{r} | p[u]r{r} CAT_TALK
CAT_HISS ::= p[u]r{r} | h[i]s{s} CAT_TALK
CAT_MIMIC ::= {ke}

FIRST(CAT_SPEAK) = FIRST(CAT_TALK) U FIRST(CAT_PURR) U FIRST(CAT_HISS) U FIRST(CAT_MIMIC)
                 = { m{e}[{o}]w, p[u]r{r}, h[i]s{s}, {ke} }
FIRST(CAT_TALK) = FIRST(m{e}[{o}]w) U FIRST(m{e}[{o}]w)
                = { m{e}[{o}]w }
FIRST(CAT_TALK') = FIRST(CAT_TALK) U FIRST(ɛ)
                 = { m{e}[{o}]w, ɛ }
FIRST(CAT_PURR) = FIRST(p[u]r{r}) U FIRST(p[u]r{r})
                = { p[u]r{r} }
FIRST(CAT_HISS) = FIRST(h[i]s{s}) U FIRST(h[i]s{s})
                = { h[i]s{s} }
FIRST(CAT_MIMIC) = FIRST({ke})
                 = { {ke} }

FOLLOW(CAT_SPEAK) = { $ }
FOLLOW(CAT_TALK) = FIRST(CAT_TALK') U FOLLOW(CAT_PURR) U FOLLOW(CAT_HISS)
                 = { m{e}[{o}]w, $ }
FOLLOW(CAT_TALK') = FOLLOW(CAT_TALK)
                  = { m{e}[{o}]w, $ }
FOLLOW(CAT_PURR) = FOLLOW(CAT_TALK)
                 = { $ }
FOLLOW(CAT_HISS) = FOLLOW(CAT_TALK)
                 = { $ }
FOLLOW(CAT_MIMIC) = FOLLOW(CAT_SPEAK)
                  = { $ }

PARSING TABLE
                $       ɛ       m{e}[{o}]w      p[u]r{r}        h[i]s{s}        {ke}
CAT_SPEAK                       CAT_TALK        CAT_PURR        CAT_HISS        CAT_MIMIC
CAT_TALK                        m{e}[{o}]w
                                CAT_TALK'
CAT_TALK'       ɛ               CAT_TALK
CAT_PURR                                        p[u]r{r}
                                                CAT_TALK
CAT_HISS                                                        h[i]s{s}
                                                                CAT_TALK
CAT_MIMIC                                                                       {ke}


TOKEN PATTERN
CAT_TALK -> /me+o*w+/
CAT_PURR -> /pu?rr+/
CAT_HISS -> /hi?ss+/
CAT_MIMIC -> /(ke)+/

<PRODUCTION> ::= <EXPRESSION> | <EXPRESSION> | ...
<EXPRESSION>: ARRAY OF <TERMINAL> AND <NON-TERMINAL>
<NON-TERMINAL> (RHS): CONTAIN STRING TO <NON-TERMINAL> (LHS)
<TERMINAL> (RHS): CONTAIN STRING TO TOKEN PATTERN
*/

export type tokenType = `CAT_${'TALK' | 'PURR' | 'HISS' | 'MIMIC'}`;

// ^ is used to start from the beginning of string
// expression flag i is used for case insensitivity
export const tokenPattern: { [key: string]: RegExp } = {
    CAT_TALK: /^me+o*w/i,
    CAT_PURR: /^pu?rr+/i,
    CAT_HISS: /^hi?ss+/i,
    CAT_MIMIC: /^(ke)+/i,
};

// UNUSED BNF CODE
interface BackusNaurForm {
    productions: BNFProduction[];
}
interface BNFProduction {
    lhs: string;
    rhs: BNFExpression[];
}
interface BNFExpression {
    terms: Array<BNFTerminal | BNFNonTerminal>;
}
interface BNFTerminal {
    type: 'terminal';
    value: string;
}
interface BNFNonTerminal {
    type: 'non-terminal';
    value: string;
}

export const bnf: BackusNaurForm = {
    productions: [
        {
            lhs: 'CAT_SPEAK',
            rhs: [
                {
                    terms: [{ type: 'terminal', value: 'CAT_TALK' }],
                },
                {
                    terms: [{ type: 'non-terminal', value: 'CAT_PURR' }],
                },
                {
                    terms: [{ type: 'non-terminal', value: 'CAT_HISS' }],
                },
                {
                    terms: [{ type: 'terminal', value: 'CAT_MIMIC' }],
                },
            ],
        },
        {
            lhs: 'CAT_TALK',
            rhs: [
                {
                    terms: [{ type: 'terminal', value: 'CAT_TALK' }],
                },
                {
                    terms: [
                        { type: 'terminal', value: 'CAT_TALK' },
                        { type: 'non-terminal', value: 'CAT_TALK' },
                    ],
                },
            ],
        },
        {
            lhs: 'CAT_PURR',
            rhs: [
                {
                    terms: [{ type: 'terminal', value: 'CAT_PURR' }],
                },
                {
                    terms: [
                        { type: 'terminal', value: 'CAT_PURR' },
                        { type: 'non-terminal', value: 'CAT_TALK' },
                    ],
                },
            ],
        },
        {
            lhs: 'CAT_HISS',
            rhs: [
                {
                    terms: [{ type: 'terminal', value: 'CAT_HISS' }],
                },
                {
                    terms: [
                        { type: 'terminal', value: 'CAT_HISS' },
                        { type: 'non-terminal', value: 'CAT_TALK' },
                    ],
                },
            ],
        },
        {
            lhs: 'CAT_MIMIC',
            rhs: [
                {
                    terms: [{ type: 'terminal', value: 'CAT_MIMIC' }],
                },
            ],
        },
    ],
};

// verify bnf (used for debugging)
for (const prod of bnf.productions) {
    for (const rhs of prod.rhs) {
        for (const t of rhs.terms) {
            if (
                t.type === 'terminal' &&
                !Object.keys(tokenPattern).find((p) => p === t.value)
            ) {
                console.error(
                    `LHS non-terminal ${prod.lhs} contain RHS terminal ${t.value} with no token pattern`
                );
            }
            if (
                t.type === 'non-terminal' &&
                !bnf.productions.find((p) => p.lhs === t.value)
            ) {
                console.error(
                    `LHS non-terminal ${prod.lhs} contain RHS non-terminal ${t.value} with no production rules`
                );
            }
        }
        if (!rhs.terms.length) {
            console.error(`LHS non-terminal ${prod.lhs} has empty term`);
        }
    }
    if (!prod.lhs.trim()) {
        console.error(`Unspecified LHS detected`);
    }
    if (prod.lhs && !prod.rhs.length) {
        console.error(`LHS non-terminal ${prod.lhs} has empty rule`);
    }
}
