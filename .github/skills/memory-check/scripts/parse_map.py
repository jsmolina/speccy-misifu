#!/usr/bin/env python3
"""
parse_map.py – Check z88dk linker map segment sizes for Misifu (ZX Spectrum 128K).

Usage:
    python3 parse_map.py [path/to/misifu.map]

Reads __<SEG>_head, __<SEG>_tail, __<SEG>_size symbols emitted by z88dk.
The CODE segment uses __CODE_END_head as the real end address.
Exits with code 1 if any segment overflows its allowed range.
"""

import re
import sys

MAP_FILE = sys.argv[1] if len(sys.argv) > 1 else "misifu.map"

# Segment limits: (org_start, max_end_exclusive)
# CODE starts at 24500 (0x5FB4) and must not reach 49152 (0xC000).
# BANKs load at 49152 (0xC000) and must stay below 65536 (0x10000).
LIMITS = {
    "CODE":   (0x5FB4, 0xC000),   # 24500 – 49151
    "BANK_3": (0xC000, 0x10000),  # 49152 – 65535
    "BANK_4": (0xC000, 0x10000),
    "BANK_6": (0xC000, 0x10000),
}

WARNING_THRESHOLD = 512  # bytes remaining before WARNING

# z88dk map symbol format:
#   __CODE_END_head  = $C21F ; ...
#   __BANK_6_tail    = $F96E ; ...
#   __BANK_6_size    = $396E ; ...
SYM_PAT = re.compile(r"(__[A-Za-z0-9_]+)\s+=\s+\$([0-9A-Fa-f]+)")

def parse_map(path):
    symbols = {}
    try:
        with open(path) as f:
            for line in f:
                m = SYM_PAT.search(line)
                if m:
                    symbols[m.group(1)] = int(m.group(2), 16)
    except FileNotFoundError:
        print(f"ERROR: map file not found: {path}")
        sys.exit(1)

    segments = {}
    # CODE: use __CODE_END_head as the real end (includes all sub-sections)
    code_start = symbols.get("__CODE_head")
    code_end   = symbols.get("__CODE_END_head")
    if code_start is not None and code_end is not None:
        segments["CODE"] = (code_start, code_end - code_start)

    for bank in ("BANK_3", "BANK_4", "BANK_6"):
        head = symbols.get(f"__{bank}_head")
        size = symbols.get(f"__{bank}_size")
        if head is not None and size is not None:
            segments[bank] = (head, size)

    return segments

def report(segments):
    any_overflow = False
    print(f"\n{'Segment':<10} {'Start (dec)':>12} {'Size':>6} {'End':>6} {'Limit':>6} {'Free':>6}  Status")
    print("-" * 68)
    for name, (_org, end_limit) in LIMITS.items():
        if name not in segments:
            print(f"{name:<10} {'(not found in map)':>50}")
            continue
        addr, size = segments[name]
        end = addr + size
        free = end_limit - end
        if free < 0:
            status = "*** OVERFLOW ***"
            any_overflow = True
        elif free < WARNING_THRESHOLD:
            status = "WARNING (low)"
        else:
            status = "OK"
        print(f"{name:<10} {addr:>12} {size:>6} {end:>6} {end_limit:>6} {free:>6}  {status}")
    print()
    if any_overflow:
        print("FAIL: one or more segments overflow their allowed range.")
        sys.exit(1)
    else:
        print("PASS: all segments fit within memory limits.")

if __name__ == "__main__":
    segs = parse_map(MAP_FILE)
    report(segs)
