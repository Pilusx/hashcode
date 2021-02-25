cd /
cd C:\Private\Hashcode2021\hashcode-2020\smartphones
g++ main.cpp -o main
g++ eval.cpp -o eval
main.exe in/a_example.in out/a_example.out
eval.exe in/a_example.in out/a_example.out

main.exe in/b_single_arm.in out/b_single_arm.out
eval.exe in/b_single_arm.in out/b_single_arm.out

main.exe in/c_few_arms.in out/c_few_arms.out
eval.exe in/c_few_arms.in out/c_few_arms.out

main.exe in/d_tight_schedule.in out/d_tight_schedule.out
eval.exe in/d_tight_schedule.in out/d_tight_schedule.out

main.exe in/e_dense_workspace.in out/e_dense_workspace.out
eval.exe in/e_dense_workspace.in out/e_dense_workspace.out

main.exe in/f_decentralized.in out/f_decentralized.out
eval.exe in/f_decentralized.in out/f_decentralized.out