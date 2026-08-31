#!/usr/bin/env bash
#
# Generic test runner shared by every module Makefile.
#
# Usage: run_tests.sh "Name:binary[:stdin-file]" ...
#
# Each argument describes one test case: a display name, the binary to run
# (path relative to the module directory), and an optional file to feed on
# stdin. A case is PASS if the binary exits 0, FAIL otherwise; on FAIL the
# tail of its output is shown to help diagnose the failure.

pass=0
fail=0

for spec in "$@"; do
  name="${spec%%:*}"
  rest="${spec#*:}"
  bin="${rest%%:*}"
  if [ "$rest" != "$bin" ]; then
    input="${rest#*:}"
  else
    input=""
  fi

  if [ ! -x "$bin" ]; then
    printf 'FAIL  %s (binary not found: %s)\n' "$name" "$bin"
    fail=$((fail + 1))
    continue
  fi

  if [ -n "$input" ]; then
    out=$("$bin" < "$input" 2>&1)
  else
    out=$("$bin" < /dev/null 2>&1)
  fi
  status=$?

  if [ "$status" -eq 0 ]; then
    printf 'PASS  %s\n' "$name"
    pass=$((pass + 1))
  else
    printf 'FAIL  %s (exit %d)\n' "$name" "$status"
    printf '%s\n' "$out" | tail -20 | sed 's/^/      /'
    fail=$((fail + 1))
  fi
done

echo
echo "Results: $pass passed, $fail failed"

[ "$fail" -eq 0 ]
