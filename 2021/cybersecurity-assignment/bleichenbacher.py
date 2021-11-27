import requests
import sys
from decimal import Decimal, getcontext
from time import time
import hashlib
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.asymmetric import rsa, padding


def int_to_bytes(val, num_bytes):
    return [(val & (0xff << pos*8)) >> pos*8 for pos in range(num_bytes)]


getcontext().prec = 2048
msg = b'1161300548'

# M = int.from_bytes(bytes, byteorder)

# M = int.from_bytes(hashlib.sha1(msg).digest(), byteorder='big', signed=False)
M = hashlib.sha1(msg).digest()
e = 3
N = Decimal(21351921173243732117382079441788929852051045833017002418852196354962291230797940944308839382705550436282035981624889509364270320266445117162936151267478466685422657034438559502181153502822996680217849257212534418509842753521738562511645261955335373489856335397711292966856373406437094557610386199517636426115096768299030652909256043773655481962707216173996768810934888276277725626372048743766100330756085350316256595762307968215134315002456901738928905228567560463104228052434269888463970193405339748744594018357137997929542420991794107158820497519339171250857727830359695745129092444677778855626461143716967541734201)
# 14851933466123225554021798960247145217975529119057852232104200462923846026617613476893716562187126299070771173273911025664275950786915142451812515818845147410399333197700074639189732037852344007362859337000
# 26264449160027792258935160504170229622819388576129399797895305452757098921157185702572543652178304333353827296803918959711080560629089003037765839380141105294311293490730592274092283853889276078418369097647

private_key = rsa.generate_private_key(public_exponent=3, key_size=2048)
signature = private_key.sign(msg, padding.PKCS1v15, hashes.SHA1())
print(signature)

padded = cryptography.hazmat.primitives.asymmetric.padding.PKCS1v15()

print(padded)


def request_respond(sig):
    print('http://localhost:8080/bleichenbacher?msg=' +
          '1161300548' + '&sig=' + str(sig))
    response = requests.get(
        url='http://localhost:8080/bleichenbacher?msg=' + '1161300548' + '&sig=' + str(sig), timeout=0.5)
    return response.status_code


# if __name__ == '__main__':
#     time_taken_to_complete = time()
#     C = Decimal((M ** e) % N)
#     s = 1
#     while (True):
#         s += 1
#         d = Decimal(C * pow(s, e) % N)
#         respond = request_respond(d)
#         if (respond == 200):
#             print('we got it bois')
#             break
#     print('time taken to complete (s):', time() - time_taken_to_complete)
