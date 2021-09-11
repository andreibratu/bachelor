# Abstract

This repository holds the code, dependency list and a PDF version of "DAuGAN: An approach for augmenting time series imbalanced datasets via latent space sampling" article. The method identifies poorly represented "episodes" of a time series in order to synthesize new data points for training.


# Reproduction

* Python3 distribution is required to be installed on the machine
* Change directory to folder containing the article's files
* Run `python3 -m venv venv` to create a virtual environment named `venv`
* Activate the Python virtual environment
    - For Windows machines: Run `venv\Scripts\activate`
    - For Unix machines: Run `source venv/bin/activate`
* Run `pip install -r requirements.txt` to install dependencies
* Run `jupyter lab` to start the Jupyter Notebook interface
* Access the `code.ipynb` notebook
* Select "Run All Cells" option from interface to execute the code. This will execute all steps in producing the augmented time-series, along with the figures used in article.
* The end result is the augmented timeseries and the reinforcement learning trading environment for carrying out the tests.
    