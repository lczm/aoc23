from typing import List, Dict, Tuple
from pprint import pprint
from dataclasses import dataclass, field, replace
from itertools import permutations
from copy import deepcopy

import typing


@dataclass
class Cond:
    cond: str
    then: str
    other: str


@dataclass
class Part:
    x: int
    m: int
    a: int
    s: int

    def sum(self):
        return self.x + self.m + self.a + self.s


@dataclass
class Bounds:
    min_x: int = field(default=1)
    max_x: int = field(default=4000)

    min_m: int = field(default=1)
    max_m: int = field(default=4000)

    min_a: int = field(default=1)
    max_a: int = field(default=4000)

    min_s: int = field(default=1)
    max_s: int = field(default=4000)

    def sum(self) -> int:
        return (
            (self.max_x - self.min_x + 1)
            * (self.max_m - self.min_m + 1)
            * (self.max_a - self.min_a + 1)
            * (self.max_s - self.min_s + 1)
        )


def get_workflow(workflows) -> Dict[str, List[str]]:
    mapping = {}
    for workflow in workflows.split("\n"):
        split = workflow.split("{")
        name = split[0]
        conditions = split[1][:-1]
        mapping[name] = conditions.split(",")
        print(mapping[name])
    return mapping


def get_parts(parts) -> List[Part]:
    p = []
    for part in parts.split("\n"):
        part = part[1:-1]
        v = part.split(",")
        x = int(v[0][2:])
        m = int(v[1][2:])
        a = int(v[2][2:])
        s = int(v[3][2:])
        p.append(Part(x, m, a, s))
    return p


# tells it whether it is true or not
def evaluate(part: Part, condition: str) -> Tuple[bool, str]:
    split = condition.split(":")
    if len(split) >= 2:
        cond, outcome = split[0], split[1]
        if cond[1] == "<":
            # print(f"Comparing < | {part.__getattribute__(cond[0])} | {cond[2:]}")
            if part.__getattribute__(cond[0]) < int(cond[2:]):
                # print("True")
                return (True, outcome)
        else:
            # print(f"Comparing > | {part.__getattribute__(cond[0])} | {cond[2:]}")
            if part.__getattribute__(cond[0]) > int(cond[2:]):
                # print("True")
                return (True, outcome)
    # print("Returning condition : ", condition)
    return (False, condition)


# it'll return either A (accepted) or R (rejected)
def compute(part: Part, func: str) -> str:
    # print(f"Workflow : {func}")
    steps = workflows[func]
    for step in steps[:-1]:
        b, out = evaluate(part, step)
        # if it passes the condition
        if b:
            # if it terminates, then end here
            if out == "A" or out == "R":
                # print("Terminating at A|R", out)
                return out
            # jump to the next workflow
            return compute(part, out)
    # if all the steps, went through, then it's the default state
    if steps[-1] == "A" or steps[-1] == "R":
        # print("Terminating at A|R", steps[-1])
        return steps[-1]
    return compute(part, steps[-1])


def part1():
    s = 0
    for part in parts:
        ret = compute(part, "in")
        if ret == "A":
            print(part)
            s += part.sum()
    print(s)
    # tests
    # ret = compute(parts[2], "in")


workflows: Dict[str, List[str]] = {}
parts: List[Part] = []

with open("./input") as file:
    lines = ("".join([line for line in file])).split("\n\n")
    workflows, parts = get_workflow(lines[0]), get_parts(lines[1])
    min_a: int = field(default=1)
    max_a: int = field(default=4000)


# part1()

# pprint(workflows)

def parse_cond(workflow: List[str]) -> List[Cond]:
    conditions = workflow[:-1]
    default = workflow[-1]

    conds = []
    for condition in conditions:
        left_split = condition.split(":")
        conds.append(Cond(left_split[0], left_split[1], default))
    return conds


def eval_cond(cond: Cond, bounds: Bounds) -> List[Tuple[bool, Bounds]]:
    cond_var, cond_operator, cond_magnitude = (
        cond.cond[0],
        cond.cond[1],
        int(cond.cond[2:]),
    )
    split_bounds = replace(bounds)

    cases = []
    true_bounds = deepcopy(bounds)
    false_bounds = deepcopy(bounds)

    # Set the bounds
    if cond_operator == "<":
        true_bounds.__setattr__("max_" + cond_var, cond_magnitude - 1)
        false_bounds.__setattr__("min_" + cond_var, cond_magnitude)
    else:
        true_bounds.__setattr__("min_" + cond_var, cond_magnitude + 1)
        false_bounds.__setattr__("max_" + cond_var, cond_magnitude)
    
    # Check bounds and add if valid
    if (true_bounds.__getattribute__("min_" + cond_var) <= 
        true_bounds.__getattribute__("max_" + cond_var)):
        cases.append((True, true_bounds))
    if (false_bounds.__getattribute__("min_" + cond_var) <= 
        false_bounds.__getattribute__("max_" + cond_var)):
        cases.append((False, false_bounds))

    return cases


global_bounds: List[Bounds] = []


def compress(workflows: Dict[str, List[str]], func: str, bounds: Bounds):
    global global_bounds
    if func == "A":
        global_bounds.append(bounds)
        return
    if func == "R":
        return

    steps = workflows[func]
    current_bounds = deepcopy(bounds)
    
    for i in range(len(steps) - 1):
        condition = steps[i]
        split = condition.split(":")
        if len(split) < 2:
            # Handle default case
            if condition == "A":
                global_bounds.append(current_bounds)
            elif condition != "R":
                compress(workflows, condition, current_bounds)
            continue
            
        cond, outcome = split[0], split[1]
        cases = eval_cond(Cond(cond, outcome, steps[-1]), current_bounds)
        
        for is_true, new_bounds in cases:
            if is_true:
                if outcome == "A":
                    global_bounds.append(new_bounds)
                elif outcome != "R":
                    compress(workflows, outcome, new_bounds)
            else:
                current_bounds = new_bounds
    
    # default case
    if steps[-1] == "A":
        global_bounds.append(current_bounds)
    elif steps[-1] != "R":
        compress(workflows, steps[-1], current_bounds)



def part2():
    pprint(workflows)
    compress(workflows, "in", Bounds())

    for gb in global_bounds:
        print(gb)

    print(sum(x.sum() for x in global_bounds))


part2()
