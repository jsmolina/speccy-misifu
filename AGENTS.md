# Misifu – AI Agent Instructions

ZX Spectrum 128K game written in C and Z80 assembly, compiled with **z88dk v2.1** (sdcc_iy clib, SP1 sprite library).

## Build

### Local (z88dk must be installed)

```sh
make compile        # optimized release build
make develop        # size-optimized build (uses --opt-code-size -zopt)
```

### Docker (preferred, no local z88dk required)

```sh
docker-compose run compile   # output goes to ./dist/
```

Or use `./makemisifu.sh` / `makemisifu.bat` for scripted builds.

Build produces `misifu.tap` by concatenating: `loader.tap screen.tap code.tap bank6.tap bank4.tap bank3.tap`.

### Sprite/asset regeneration (requires z88dk tools in PATH)

```sh
make sprites        # regenerate all sprite ASM from PNGs
make prota          # cat sprite
make dogsprites
make clothes
# etc. – see Makefile for individual targets
```

## Memory layout (128K, CRITICAL)

| Region      | Address      | Purpose                        |
| ----------- | ------------ | ------------------------------ |
| CODE (main) | 24500–~49151 | C code + data (contiguous RAM) |
| BANK 3      | 49152        | Level data bank                |
| BANK 4      | 49152        | Level data bank                |
| BANK 6      | 49152        | AY music (vt_sound library)    |
| Screen      | 16384        | Splash screen `.scr`           |
| Stack       | `0xD000`     | Set via `REGISTER_SP` pragma   |

**Memory is the main constraint.** The CODE segment must not overflow below BANK start (49152). Watch `.map` output after every build. Key pragmas live in [zpragma.inc](zpragma.inc):

- `CRT_ORG_CODE = 24500`
- `REGISTER_SP  = 0xD000`
- Stack size: 128 bytes (`CRT_STACK_SIZE`)
- No stdio heap, no FILE\*, no atexit

## Project structure

| Path                                    | Content                                                 |
| --------------------------------------- | ------------------------------------------------------- |
| `misifu.c`                              | Main game loop, entry point                             |
| `level1.c` – `level7.c`, `level_last.c` | One C file per level                                    |
| `defines.h` / `defines.c`               | Shared constants and game-state defines                 |
| `int.c` / `int.asm`                     | Interrupt handler                                       |
| `zpragma.inc`                           | z88dk CRT compile-time config                           |
| `zproject.lst`                          | Source file list passed to `zcc` with `@`               |
| `build/`                                | Generated ASM sprites (`protar.asm`, `dogr.asm`, etc.)  |
| `ay/`                                   | AY music engine (vt_sound), PT3 files, `ay_music.asm`   |
| `background/`                           | Python scripts to convert PNGs to UDG/tile header files |
| `sprites/`                              | Source PNG sprite sheets                                |
| `loader.bas`                            | BASIC loader; `loader.tap` is pre-built                 |

## Code conventions

- C dialect: SDCC (not GCC). Avoid GCC-only extensions.
- Use `__at(addr)` or linker sections (`#pragma section`) to place data in specific banks.
- Bank data goes into sections `BANK_3`, `BANK_4`, `BANK_6` (set via `zobjcopy` in Makefile).
- SP1 library used for sprites: `<arch/zx/sp1.h>`.
- Input via `<input.h>` (z88dk).
- Constants: uppercase `#define` in `defines.h`. No enums (SDCC overhead).
- No dynamic allocation in game loops. Block allocator (`CLIB_BALLOC_TABLE_SIZE = 1`) is the only heap.

## Key pitfalls

- **SDCC calling conventions differ from GCC** – no VLAs, limited stack usage.
- **Adding large arrays or strings to main CODE bank will overflow memory.** Place level-specific data in the correct bank section.
- **Bank switching** is manual; only one bank (3, 4, or 6) is paged in at `0xC000` at a time.
- The `.map` file (generated as `misifu.map`) shows segment sizes; check it after builds.
- Docker build uses z88dk v2.1 (pinned). Local z88dk must be the same version to reproduce builds.
