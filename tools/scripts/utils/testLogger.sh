#!/bin/bash

git_dir=$(git rev-parse --show-toplevel)
cd $git_dir 1>testLogger.log
source $(pwd)/tools/scripts/utils/logger.sh 1>testLogger.log
cd - 1> testLogger.log
rm testLogger.log

while getopts 'v' flag;
do
    case "${flag}" in
        v)
            echo "VERBOSE"
            CMAKE_CURRENT_LOG_LEVEL=CMAKE_LOG_LEVEL_TRACE
        ;;
        ?)
            echo "script usage: $(basename \$0) [-v]" >&2
            exit 1
        ;;
    esac
done



log_trace "Testing LOG TRACE"
log_debug "Testing LOG DEBUG"
log_info "Testing LOG INFO"
log_warn "Testing LOG WARN"
log_error "Testing LOG ERROR"
log_fatal "Testing LOG FATAL"

log_info "Exiting..."
