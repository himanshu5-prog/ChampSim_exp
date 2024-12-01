### Branch predictor: Always not taken
./config.sh myConfig/champsim_config_branch_pred_always_not_taken.json
make
#set benchmark_name $benchmark_dir\/$perlbench
#puts stdout $benchmark_name
./bin/champsim --warmup-instructions 1000000 --simulation-instructions 50000000 benchmark/400.perlbench-41B.champsimtrace.xz > myLog/branch_not_taken_400_perlbench_41B.log
./bin/champsim --warmup-instructions 1000000 --simulation-instructions 50000000 benchmark/401.bzip2-38B.champsimtrace.xz > myLog/branch_not_taken_401_bzip2_38B.log
./bin/champsim --warmup-instructions 1000000 --simulation-instructions 50000000 benchmark/403.gcc-16B.champsimtrace.xz > myLog/branch_not_taken_403_gcc_41B.log
./bin/champsim --warmup-instructions 1000000 --simulation-instructions 50000000 benchmark/429.mcf-22B.champsimtrace.xz > myLog/branch_not_taken_429_mcf_22B.log

## Branch predictor: Always taken
./config.sh myConfig/champsim_config_branch_pred_always_taken.json
make

./bin/champsim --warmup-instructions 1000000 --simulation-instructions 50000000 benchmark/400.perlbench-41B.champsimtrace.xz > myLog/branch_taken_400_perlbench_41B.log
./bin/champsim --warmup-instructions 1000000 --simulation-instructions 50000000 benchmark/401.bzip2-38B.champsimtrace.xz > myLog/branch_taken_401_bzip2_38B.log
./bin/champsim --warmup-instructions 1000000 --simulation-instructions 50000000 benchmark/403.gcc-16B.champsimtrace.xz > myLog/branch_taken_403_gcc_41B.log
./bin/champsim --warmup-instructions 1000000 --simulation-instructions 50000000 benchmark/429.mcf-22B.champsimtrace.xz > myLog/branch_taken_429_mcf_22B.log

## Branch predictor: Bimodal
./config.sh myConfig/champsim_config_branch_pred_bimodal.json
make

./bin/champsim --warmup-instructions 1000000 --simulation-instructions 50000000 benchmark/400.perlbench-41B.champsimtrace.xz > myLog/branch_bimodal_400_perlbench_41B.log
./bin/champsim --warmup-instructions 1000000 --simulation-instructions 50000000 benchmark/401.bzip2-38B.champsimtrace.xz > myLog/branch_bimodal_401_bzip2_38B.log
./bin/champsim --warmup-instructions 1000000 --simulation-instructions 50000000 benchmark/403.gcc-16B.champsimtrace.xz > myLog/branch_bimodal_403_gcc_41B.log
./bin/champsim --warmup-instructions 1000000 --simulation-instructions 50000000 benchmark/429.mcf-22B.champsimtrace.xz > myLog/branch_bimodal_429_mcf_22B.log

## Branch predictor: Bimodal - 3 bits
#./config.sh myConfig/champsim_config_branch_pred_bimodal_3bits.json
#make

#./bin/champsim --warmup-instructions 1000000 --simulation-instructions 50000000 benchmark/400.perlbench-41B.champsimtrace.xz > myLog/branch_bimodal_3bits_400_perlbench_41B.log
#./bin/champsim --warmup-instructions 1000000 --simulation-instructions 50000000 benchmark/401.bzip2-38B.champsimtrace.xz > myLog/branch_bimodal_3bits_401_bzip2_38B.log
#./bin/champsim --warmup-instructions 1000000 --simulation-instructions 50000000 benchmark/403.gcc-16B.champsimtrace.xz > myLog/branch_bimodal_3bits_403_gcc_41B.log
#./bin/champsim --warmup-instructions 1000000 --simulation-instructions 50000000 benchmark/429.mcf-22B.champsimtrace.xz > myLog/branch_bimodal_3bits_429_mcf_22B.log

./config.sh myConfig/champsim_config_branch_pred_local_history.json
make

./bin/champsim --warmup-instructions 1000000 --simulation-instructions 50000000 benchmark/400.perlbench-41B.champsimtrace.xz > myLog/branch_local_hist_400_perlbench_41B.log
./bin/champsim --warmup-instructions 1000000 --simulation-instructions 50000000 benchmark/401.bzip2-38B.champsimtrace.xz > myLog/branch_local_hist_401_bzip2_38B.log
./bin/champsim --warmup-instructions 1000000 --simulation-instructions 50000000 benchmark/403.gcc-16B.champsimtrace.xz > myLog/branch_local_hist_403_gcc_41B.log
./bin/champsim --warmup-instructions 1000000 --simulation-instructions 50000000 benchmark/429.mcf-22B.champsimtrace.xz > myLog/branch_local_hist_429_mcf_22B.log

./config.sh myConfig/champsim_config_branch_pred_gshare.json
make

./bin/champsim --warmup-instructions 1000000 --simulation-instructions 50000000 benchmark/400.perlbench-41B.champsimtrace.xz > myLog/branch_gshare_400_perlbench_41B.log
./bin/champsim --warmup-instructions 1000000 --simulation-instructions 50000000 benchmark/401.bzip2-38B.champsimtrace.xz > myLog/branch_gshare_401_bzip2_38B.log
./bin/champsim --warmup-instructions 1000000 --simulation-instructions 50000000 benchmark/403.gcc-16B.champsimtrace.xz > myLog/branch_gshare_403_gcc_41B.log
./bin/champsim --warmup-instructions 1000000 --simulation-instructions 50000000 benchmark/429.mcf-22B.champsimtrace.xz > myLog/branch_gshare_429_mcf_22B.log

./config.sh myConfig/champsim_config_branch_pred_comb_local_glob.json
make

./bin/champsim --warmup-instructions 1000000 --simulation-instructions 50000000 benchmark/400.perlbench-41B.champsimtrace.xz > myLog/branch_combo_400_perlbench_41B.log
./bin/champsim --warmup-instructions 1000000 --simulation-instructions 50000000 benchmark/401.bzip2-38B.champsimtrace.xz > myLog/branch_combo_401_bzip2_38B.log
./bin/champsim --warmup-instructions 1000000 --simulation-instructions 50000000 benchmark/403.gcc-16B.champsimtrace.xz > myLog/branch_combo_403_gcc_41B.log
./bin/champsim --warmup-instructions 1000000 --simulation-instructions 50000000 benchmark/429.mcf-22B.champsimtrace.xz > myLog/branch_combo_429_mcf_22B.log

./config.sh myConfig/champsim_config_branch_pred_comb_local_glob_hyst.json
make

./bin/champsim --warmup-instructions 1000000 --simulation-instructions 50000000 benchmark/400.perlbench-41B.champsimtrace.xz > myLog/branch_combo_hyst_400_perlbench_41B.log
./bin/champsim --warmup-instructions 1000000 --simulation-instructions 50000000 benchmark/401.bzip2-38B.champsimtrace.xz > myLog/branch_combo_hyst_401_bzip2_38B.log
./bin/champsim --warmup-instructions 1000000 --simulation-instructions 50000000 benchmark/403.gcc-16B.champsimtrace.xz > myLog/branch_combo_hyst_403_gcc_41B.log
./bin/champsim --warmup-instructions 1000000 --simulation-instructions 50000000 benchmark/429.mcf-22B.champsimtrace.xz > myLog/branch_combo_hyst_429_mcf_22B.log
