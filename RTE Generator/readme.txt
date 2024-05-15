Please read the following help file, which explains

- How to install the tool on your computer
- Guides you through a first project setup

\RTELight_v<xyz>\gui\RteGui\help\index.html

Known Problems
===============

Q: During the installation, the Python package installer complains about incompatabilties
A: Please install Python version 3.10. Make sure, that this version is called by default.

Q: When pressing Save & Generate, the GUI continues asking for the correct path.
A: Very likely the required packages for the gnerator are mussing. Note, that you have to run the package installer twice, once for the GUI and once for the Generator.

Q: When pressing Save & Generate, Python throws a weird exception
A: Please update the template path on the main tab. Later versions of the tool support template folder for different RTOS variants. 
   I.e. you need to add the RTOS Path to templates, e.g. .....\templates\erika
