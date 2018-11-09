echo "+++++ BUILDING EX1 ++++++"
cp ../../Exercise-solutions/01_build/*.* src/
scons
echo "+++++ BUILDING EX2 ++++++"
cp ../../Exercise-solutions/02_types/*.* src/
scons
echo "+++++ BUILDING EX3 ++++++"
cp ../../Exercise-solutions/03_flow_control/*.* src/
scons
echo "+++++ BUILDING EX4 ++++++"
cp ../../Exercise-solutions/04_pointers/*.* src/
scons
echo "+++++ BUILDING EX5 ++++++"
cp ../../Exercise-solutions/05_hardware_manipulation/*.* src/
scons
echo "+++++ BUILDING EX6 ++++++"
cp ../../Exercise-solutions/06_wms/*.* src/
scons
echo "+++++ BUILDING EX7 ++++++"
cp ../../Exercise-solutions/07_functions/*.* src/
scons
echo "+++++ BUILDING EX8 ++++++"
cp ../../Exercise-solutions/08_program_structure/*.* src/
scons
echo "+++++ BUILDING EX9 ++++++"
cp ../../Exercise-solutions/09_arrays/*.* src/
scons
echo "+++++ BUILDING EX10 ++++++"
cp ../../Exercise-solutions/10_structures/*.* src/
scons
echo "+++++ BUILDING EX11 ++++++"
cp ../../Exercise-solutions/11_bit_fields/*.* src/
scons
echo "+++++ BUILDING EX12 ++++++"
cp ../../Exercise-solutions/12_interrupts/*.* src/
scons
echo "+++++ BUILDING EX13 ++++++"
cp ../../Exercise-solutions/13_preprocessor/*.* src/
scons
echo "+++++ BUILDING EX14 ++++++"
cp ../../Exercise-solutions/14_concurrency/*.* src/
scons --rtos-build
echo "+++++ BUILDING EX15 ++++++"
cp ../../Exercise-solutions/15_task_synchronisation/*.* src/
scons --rtos-build