#!/usr/bin/python3
import argparse
from typing import Tuple, Union
from random import random, choice, randint


def positive_int(value: str) -> int:
    """
    Check if number is positive
    RETURN: if positive -> return it
            else -> raise an error
    """
    value = int(value)
    if value <= 0:
        raise argparse.ArgumentTypeError("%s is an invalid positive int value" % value)
    return value

def gen_num(config: argparse.Namespace) -> Union[int, float]:
    """
    Generate random number using information in config
    """
    if config.float:
        x = round(random() * config.boundary, config.precision)
    else:
        x = randint(1, config.boundary)
    
    if random() < 0.5:
        x *= -1

    return x

def gen_exp(config: argparse.Namespace) -> Tuple[str, float]:
    """
    Generate random expression
    WARNING: generates until expression doesn't have divisions by zero
    """
    while True:
        exp = '('
        parant_count = 0
        for _ in range(config.numberop):
            exp += str(gen_num(config))

            while parant_count > 0 and random() < 0.15:
                exp += ')'
                parant_count -= 1
            exp += choice(['+', '-', '*', '/'])
            while random() < 0.1:
                exp += '('
                parant_count += 1

        exp += str(gen_num(config)) + ')' * (parant_count + 1)

        try:
            res = eval(exp)
        except:
            continue

        return (exp, res)

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('-n', '--numberop', help='Number of operations', type=positive_int, default=100)
    parser.add_argument('-b', '--boundary', help='Random numbers boundary (-b, b)', type=positive_int, default=10)
    parser.add_argument('-f', '--float', help='Use floats', type=bool, nargs='?', const=True, default=False)
    parser.add_argument('-p', '--precision', help='Float precision', type=positive_int, default=3)
    parser.add_argument('-a', '--answer', help='Also print answer', type=bool, nargs='?', const=True, default=False)
    config = parser.parse_args()

    exp, res = gen_exp(config)
    print(exp, end=' ')
    
    if config.answer:
        print(res, end='')


if __name__ == "__main__":
    main()