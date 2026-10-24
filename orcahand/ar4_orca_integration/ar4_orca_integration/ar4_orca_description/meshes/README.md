# ar4_orca_description/meshes

Custom mounting parts (arm <-> hand connector, brackets, ...) go here.
Referenced from config/mount.yaml as
`package://ar4_orca_description/meshes/<file>.stl`.

After adding a NEW file, rebuild once (symlink-install links files, not folders):

    cd ~/RobotHand && colcon build --symlink-install --packages-select ar4_orca_description
