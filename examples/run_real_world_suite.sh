#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BIN="$ROOT_DIR/bin/Complier"
SRC_DIR="$ROOT_DIR/examples/source"

pass_files=(
  "real_world_all_features_pass.tq"
  "real_world_pass.tq"
  "functions_demo.tq"
  "multi_decl_demo.tq"
  "stress_suite.tq"
  "test.tq"
)

fail_files=(
  "real_world_fail_type.tq"
  "real_world_fail_immutable.tq"
  "real_world_fail_undeclared.tq"
  "real_world_fail_argcount.tq"
  "real_world_fail_return_type.tq"
  "real_world_fail_redecl.tq"
)

echo "Using: $BIN"
echo

run_one() {
  local file="$1"
  local expect="$2"   # 0 or 1 (1 means expect failure)
  local timeout_s="${3:-}"
  local cmd=()

  if [[ -n "$timeout_s" ]]; then
    cmd=(timeout "$timeout_s" "$BIN")
  else
    cmd=("$BIN")
  fi

  set +e
  local out
  out="$("${cmd[@]}" < "$SRC_DIR/$file" 2>&1)"
  local st=$?
  set -e

  local ok="NO"
  if [[ "$expect" == "0" && "$st" == "0" ]]; then ok="YES"; fi
  if [[ "$expect" == "1" && "$st" != "0" ]]; then ok="YES"; fi

  printf "%-34s  exit=%-3s  expected=%s  OK=%s\n" "$file" "$st" "$expect" "$ok"

  if [[ "$ok" == "NO" ]]; then
    echo "---- output (first 30 lines) ----"
    echo "$out" | sed -n '1,30p'
    echo "--------------------------------"
  fi
}

echo "[PASS suites] (expect exit 0)"
for f in "${pass_files[@]}"; do
  run_one "$f" 0
done
echo

echo "[FAIL suites] (expect non-zero exit)"
for f in "${fail_files[@]}"; do
  run_one "$f" 1
done
echo

echo "[INFINITE suite] (expect timeout exit 124)"
set +e
out="$(timeout 1s "$BIN" < "$SRC_DIR/real_world_infinite_while.tq" 2>&1)"
st=$?
set -e
ok="NO"
if [[ "$st" == "124" ]]; then ok="YES"; fi
printf "%-34s  exit=%-3s  expected=124  OK=%s\n" "real_world_infinite_while.tq" "$st" "$ok"
if [[ "$ok" == "NO" ]]; then
  echo "---- output (first 30 lines) ----"
  echo "$out" | sed -n '1,30p'
  echo "--------------------------------"
fi

