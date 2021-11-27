const http = require('http');

let hex = '0123456789abcdef';
let hmac = 'f95f840d04d24e5d9061890c90ecd6b84edc';

for (let i = 0; i < hex.length; i++) {
    for (let j = 0; j < hex.length; j++) {
        for (let k = 0; k < hex.length; k++) {
            for (let l = 0; l < hex.length; l++) {
                let next = hmac + hex[i] + hex[j] + hex[k] + hex[l];
                http.get(
                    `http://localhost:8080/badtiming?file=1171100932&hmac=${next}`,
                    (res) => {
                        let data = '';
                        res.on('data', (d) => {
                            data += d;
                        });
                        res.on('end', () => {});
                    }
                ).on('error', (err) => {
                    console.log('error' + err.message);
                });
            }
        }
    }
}

// try {
//     const { data } = axios
//         .get(
//             `http://localhost:8080/badtiming?file=1171100932&hmac=${next}`
//         )
//         .then((data) => console.log(data));
// } catch (e) {}
