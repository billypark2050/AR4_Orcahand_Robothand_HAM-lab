from glob import glob
from setuptools import setup

package_name = "orcahand_driver"

setup(
    name=package_name,
    version="0.1.0",
    packages=[package_name],
    data_files=[
        ("share/ament_index/resource_index/packages", ["resource/" + package_name]),
        ("share/" + package_name, ["package.xml"]),
        ("share/" + package_name + "/launch", glob("launch/*.py")),
        ("share/" + package_name + "/config", glob("config/*.yaml")),
    ],
    install_requires=["setuptools"],
    zip_safe=True,
    maintainer="Billy Park",
    maintainer_email="billypark2050@gmail.com",
    description="ROS 2 driver for the ORCA Hand (orca_core wrapper)",
    license="MIT",
    tests_require=["pytest"],
    entry_points={
        "console_scripts": [
            "orcahand_driver = orcahand_driver.hand_driver_node:main",
            "hand_pose = orcahand_driver.hand_pose:main",
            "slider_relay = orcahand_driver.slider_relay:main",
        ],
    },
)
