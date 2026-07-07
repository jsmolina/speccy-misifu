---
name: memory-check
description: "Parse misifu.map after a build and report CODE/BANK segment sizes vs limits. Use when: checking memory usage, verifying a build fits in memory, debugging memory overflow, monitoring segment sizes after adding code or data to the ZX Spectrum 128K game."
argument-hint: "Optional: path to .map file (default: misifu.map)"
---

# Memory Check – ZX Spectrum 128K (Misifu)

Parses the z88dk linker map file and reports whether each segment fits within its allowed address range.

## When to Use

- After `make compile` or `make develop` to verify no overflow
- After adding new code, arrays, or strings to check impact
- When the build produces unexpected segment sizes
- When diagnosing "segment too large" linker errors

## Memory Limits (from [zpragma.inc](../../zpragma.inc))

| Segment     | Start | Max End | Max Size    |
| ----------- | ----- | ------- | ----------- |
| CODE (main) | 24500 | 49151   | 24651 bytes |
| BANK_3      | 49152 | 65535   | 16383 bytes |
| BANK_4      | 49152 | 65535   | 16383 bytes |
| BANK_6      | 49152 | 65535   | 16383 bytes |

> Stack is at `0xD000` (53248). CODE must not reach 49152.

## Procedure

1. **Build first** (if no map file exists or code changed):

   ```sh
   docker-compose run compile
   # or, if z88dk is installed locally:
   make compile
   ```

2. **Locate the map file**: `dist/misifu.map` (default output path, or user-supplied path).

3. **Parse segment sizes** using [scripts/parse_map.py](./scripts/parse_map.py):

   ```sh
   python3 .github/skills/memory-check/scripts/parse_map.py dist/misifu.map
   ```

4. **Interpret the output**:
   - `OK` – segment fits with headroom shown
   - `WARNING` – less than 512 bytes remaining (close to limit)
   - `OVERFLOW` – segment exceeds its allowed range (build will not run correctly)

5. **Act on findings**:
   - If CODE overflows → move large arrays or level-specific data into a `BANK_3`/`BANK_4` section using `#pragma section` and update [zproject.lst](../../zproject.lst)
   - If a BANK overflows → split data across multiple banks or compress assets
   - Re-build and re-run the check after fixes

## Notes

- The `.map` file is only generated when the `-m` flag is passed to `zcc` (present in both `compile` and `develop` Makefile targets).
- Segment names in the map may appear as `_CODE`, `CODE`, `BANK_3`, etc. — the script handles common variants.
- Bank 6 holds the AY music engine (`vt_sound`); avoid adding game data there.
