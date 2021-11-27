# fast solution and recoverable from fail
# if you encounter it repeat too often, just retry it with known hash down here into result_hmac
# if there is no hit regardless, try reverting to last known hash and removing each byte; NOTE: it must be even number hmac length
# need to play around with the value to proceed and check the timing (for my case, a successful attack has significant change by ~0.03s)

import requests
from time import time

hexdigits = '0123456789abcdef'

known_sleep_time = 0.025
# load time in second per 2 hex or 1 byte; take avg, play with the value until u get sweet spot
# lower number is more lenient, but produce false positive as it gets closer to result
# tolerance is done so the request and the loop time deviation that happen behind the scene is taken care of
delay_time_tol = known_sleep_time + 0.005
repeat_test = 16
file_name = '1171302706'


def request_respond(hmac):
    response = requests.get(
        url='http://localhost:8080/badtiming?file=' + file_name + '&hmac=' + hmac, timeout=5)
    return response.status_code, response.elapsed.total_seconds()


def cracked_hmac(cracked, padding):
    combination = ''
    time_taken = 0
    start_time = time()
    avg_start_time = 0
    for _ in range(repeat_test):
        hmac = cracked.ljust(padding, '0')
        _, time_taken = request_respond(hmac)
        avg_start_time += time_taken
    previous_time = avg_start_time / repeat_test
    print('avg load time (s):', round(previous_time, 3))
    for _ in range(repeat_test):
        avg_time_taken = 0
        for hex0 in hexdigits:
            print('checking ' + cracked + hex0 + '#')
            for hex1 in hexdigits:
                combination = hex0 + hex1
                hmac = (cracked + combination).ljust(padding, '0')
                respond, time_taken = request_respond(hmac)
                avg_time_taken += time_taken
                if (respond == 200):
                    print('oh shit (s):', round(
                        time() - start_time, 3), 'load time (s):', round(time_taken, 3), 'previous time (s):', round(previous_time, 3))
                    return combination
                if (time_taken > previous_time + delay_time_tol):
                    print('found hit (s):', round(
                        time() - start_time, 3), 'load time (s):', round(time_taken, 3), 'previous time (s):', round(previous_time, 3))
                    return combination
        print('no hit, test again; avg load time (s):', round(
            avg_time_taken / (16 * 16), 3), 'previous time (s):', round(previous_time, 3))
        # k1v4l reset previous time to avg time taken
        previous_time = avg_time_taken / (16 * 16)
    # if no hit after several test, restart
    print('no hit (s):', round(time() - start_time, 3))
    return '00'


if __name__ == '__main__':
    padding_length = 40
    # you can insert the already known hash here (don't include the padding)
    result_hmac = ''

    time_taken_to_complete = time()
    for _ in range(20):
        if (len(result_hmac) >= padding_length):
            break

        next_hex = cracked_hmac(
            result_hmac, padding_length)
        result_hmac += next_hex
        print('current result:', result_hmac.ljust(
            padding_length, '0'), 'length:', len(result_hmac))
    print('time taken to complete (m):', (time() - time_taken_to_complete) / 60)
