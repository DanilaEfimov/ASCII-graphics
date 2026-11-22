#!/usr/bin/env bash
# Коммитит проект по шагам, между коммитами пауза ~INTERVAL секунд ± JITTER.
# Сообщения в формате "type(scope): message".
#
#   ./scripts/commit_steps.sh               # с паузами (по умолчанию ~20 мин ± 5 мин)
#   ./scripts/commit_steps.sh --no-wait     # без пауз
#   ./scripts/commit_steps.sh --dry-run     # только показать план
#   INTERVAL=600 JITTER=120 ./scripts/commit_steps.sh
#
# Можно прервать (Ctrl-C) и запустить снова: уже закоммиченные шаги пропускаются.
# Запускать лучше в tmux/screen или через nohup.

set -euo pipefail

INTERVAL="${INTERVAL:-1200}"   # базовая пауза, секунды
JITTER="${JITTER:-300}"        # случайный разброс ±, секунды
DRY_RUN=0
WAIT=1

for arg in "$@"; do
    case "$arg" in
        --dry-run) DRY_RUN=1 ;;
        --no-wait) WAIT=0 ;;
        -h|--help) sed -n '2,11p' "$0"; exit 0 ;;
        *) echo "unknown option: $arg" >&2; exit 1 ;;
    esac
done

cd "$(dirname "$0")/.."

# "сообщение|файлы через пробел"
STEPS=(
    "chore(repo): add gitignore, editorconfig, clang-format and commit helper|.gitignore .editorconfig .clang-format scripts/commit_steps.sh"
    "feat(coord): add compile-time coordinate category traits|include/coord_traits.hpp"
    "feat(cell): add Cell with float bounds accessor|include/cell.hpp"
    "feat(bubble): add Bubble with center and radius control|include/bubble.hpp"
    "feat(physics): clip bubble by cell, clamp to walls, compute pressure|include/physics.hpp"
    "feat(app): add main loop, keyboard control and grow bubble on Space|src/main.cpp"
    "build(cmake): link SFML 3 and fix include directories|CMakeLists.txt"
    "docs(readme): describe controls, build and project layout|README.md"
)

if [[ $DRY_RUN -eq 0 ]] && ! git rev-parse --is-inside-work-tree >/dev/null 2>&1; then
    git init -q -b main
fi

committed=0
for step in "${STEPS[@]}"; do
    msg="${step%%|*}"
    files="${step#*|}"

    if [[ $DRY_RUN -eq 1 ]]; then
        printf '[dry-run] %s\n           files: %s\n' "$msg" "$files"
        continue
    fi

    missing=0
    for f in $files; do
        [[ -e "$f" ]] || { echo "skip (missing $f): $msg"; missing=1; break; }
    done
    [[ $missing -eq 1 ]] && continue

    # shellcheck disable=SC2086
    if git add -- $files && git diff --cached --quiet; then
        echo "skip (nothing to commit): $msg"
        continue
    fi

    if [[ $committed -gt 0 && $WAIT -eq 1 ]]; then
        delay=$(( INTERVAL + RANDOM % (2 * JITTER + 1) - JITTER ))
        (( delay < 0 )) && delay=0
        printf 'sleeping %dm%02ds before next commit...\n' $(( delay / 60 )) $(( delay % 60 ))
        sleep "$delay"
    fi

    git commit -q -m "$msg"
    echo "committed: $msg"
    committed=$(( committed + 1 ))
done

echo "done, $committed commit(s)"
