# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file './ai.ui'
#
# Created by: PyQt5 UI code generator 5.13.0
#
# WARNING! All changes made in this file will be lost!

import numpy as np
from PyQt5 import QtGui
from PyQt5.QtCore import QObject, pyqtSlot
from matplotlib.backends.qt_compat import QtCore, QtWidgets, is_pyqt5

if is_pyqt5():
    pass
else:
    from matplotlib.backends.backend_qt4agg import (
        FigureCanvas)
from matplotlib.figure import Figure

from ui.validation_worker import ValidationWorker
from ui.values import default_values, approaches
from ui.worker import Worker


class Ui_MainWindow(QObject):
    """"
    Note: class generated by Designer will inherit from `object`.
    It may not be necessary to set the parent to QObject in order to declare slots.
    """

    def __init__(self):
        QObject.__init__(self)
        self.worker = Worker()
        self.validation_worker = ValidationWorker(data_points=30, evaluations=100)
        self.worker.finished.connect(self._done_slot)
        self.validation_worker.finished.connect(self._validation_done_slot)
        self.validation_worker.fitness_update.connect(self._fitness_update_slot)

    def __workers_active(self) -> bool:
        """Check if worker threads are still alive."""
        return self.worker.running or self.validation_worker.running

    def __update_calculate_button(self):
        """Allow new task only if workers have finished."""
        if not self.__workers_active():
            self.calculateButton.setText('Calculate')

    def __reset_ui(self):
        """Reset reporting related widgets between calculations."""
        self.averageValueLabel.setText('N/A')
        self.medianValueLabel.setText('N/A')
        self.resultPlot.setText('')
        self.resultPlot.setStyleSheet('')
        self.fitnessPlot.figure = Figure(figsize=(5,5))
        self.fitnessPlot.draw()
        self.calculateButton.setText('Working..')

    """Slot answering QThread's finished signal."""
    def _done_slot(self):
        """Print identified optimum or the closest solution."""
        # solution = self._to_string(self.worker.result[0])
        solution = str(self.worker.result[0])
        fitness = self.worker.result[1]
        if fitness == 0:
            self.resultPlot.setStyleSheet('color: green')
            self.resultPlot.setText(f'Optimum: {solution}')
        else:
            self.resultPlot.setStyleSheet('color: red')
            self.resultPlot.setText(f'Close approximation: {solution}')

    def _validation_done_slot(self):
        """Report median and average for all evaluation trials."""
        validation_result = self.validation_worker.results
        avg, med = np.average(validation_result), np.median(validation_result)
        self.averageValueLabel.setText(str(avg))
        self.medianValueLabel.setText(str(med))
        self.__update_calculate_button()

    @pyqtSlot(list, list)
    def _fitness_update_slot(self, x, y):
        """Plot the fitness of last evaluations."""
        ax = self.fitnessPlot.figure.gca()
        ax.clear()
        ax.set_yticks([])
        ax.set_xticks([])
        self.fitnessPlot.figure.subplots().plot(x, y)
        self.fitnessPlot.draw()

    """Slot answering QT's `clicked` signal."""
    def _calculate_button_clicked(self):
        if not self.__workers_active():
            tab_idx = self.configTabWidget.currentIndex()
            args, valid_args = (), ()
            self.__reset_ui()

            if tab_idx == 0:
                args = (self.hcNInput.value(), self.hcRunsInput.value())
                valid_args = (self.hcNInput.value(), 30)

            if tab_idx == 1:
                args = (self.geneticNInput.value(), self.geneticPopSizeInput.value(),
                        self.geneticPopReplaceInput.value(), self.geneticTournamentSizeInput.value(),
                        self.geneticRunsInput.value(), self.geneticMutationChanceInput.value())
                valid_args = (self.geneticNInput.value(), 40, self.geneticPopReplaceInput.value(),
                              self.geneticTournamentSizeInput.value(), 30, self.geneticMutationChanceInput.value())

            if tab_idx == 2:
                args = (self.psoNInput.value(), self.psoRunsInput.value(), self.psoSwarmSizeInput.value(),
                        self.psoWInput.value(), self.psoC1Input.value(), self.psoC2Input.value())
                valid_args = (self.psoNInput.value(), 30, 40, self.psoWInput.value(), self.psoC1Input.value(), self.psoC2Input.value())

            method_call = approaches[tab_idx]

            self.worker.set_task(method_call, args)
            self.validation_worker.set_task(method_call, valid_args)
            self.worker.start()
            self.validation_worker.start()

    def _reset_parameters(self):
        current_tab_idx = self.configTabWidget.currentIndex()
        for k, v in default_values[current_tab_idx].items():
            combobox = self.__getattribute__(k)
            combobox.setValue(v)

    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(959, 678)
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap("../.designer/.designer/Downloads/Doge-Head-PNG-Clipart.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        MainWindow.setWindowIcon(icon)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.horizontalLayoutWidget_2 = QtWidgets.QWidget(self.centralwidget)
        self.horizontalLayoutWidget_2.setGeometry(QtCore.QRect(20, 10, 1003, 661))
        self.horizontalLayoutWidget_2.setObjectName("horizontalLayoutWidget_2")
        self.configLayout = QtWidgets.QHBoxLayout(self.horizontalLayoutWidget_2)
        self.configLayout.setContentsMargins(0, 0, 0, 0)
        self.configLayout.setObjectName("configLayout")
        spacerItem = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.configLayout.addItem(spacerItem)
        self.configTabWidget = QtWidgets.QTabWidget(self.horizontalLayoutWidget_2)
        self.configTabWidget.setMinimumSize(QtCore.QSize(450, 0))
        self.configTabWidget.setObjectName("configTabWidget")
        self.climbTab = QtWidgets.QWidget()
        self.climbTab.setObjectName("climbTab")
        self.formLayoutWidget = QtWidgets.QWidget(self.climbTab)
        self.formLayoutWidget.setGeometry(QtCore.QRect(-1, -1, 451, 631))
        self.formLayoutWidget.setObjectName("formLayoutWidget")
        self.formLayout = QtWidgets.QFormLayout(self.formLayoutWidget)
        self.formLayout.setLabelAlignment(QtCore.Qt.AlignLeading|QtCore.Qt.AlignLeft|QtCore.Qt.AlignVCenter)
        self.formLayout.setFormAlignment(QtCore.Qt.AlignLeading|QtCore.Qt.AlignLeft|QtCore.Qt.AlignVCenter)
        self.formLayout.setContentsMargins(0, 0, 0, 0)
        self.formLayout.setObjectName("formLayout")
        self.hcNLabel = QtWidgets.QLabel(self.formLayoutWidget)
        self.hcNLabel.setObjectName("hcNLabel")
        self.formLayout.setWidget(0, QtWidgets.QFormLayout.LabelRole, self.hcNLabel)
        self.hcNInput = QtWidgets.QSpinBox(self.formLayoutWidget)
        self.hcNInput.setMaximumSize(QtCore.QSize(300, 16777215))
        self.hcNInput.setMinimum(2)
        self.hcNInput.setMaximum(10)
        self.hcNInput.setProperty("value", 3)
        self.hcNInput.setObjectName("hcNInput")
        self.formLayout.setWidget(0, QtWidgets.QFormLayout.FieldRole, self.hcNInput)
        self.hcRunsLabel = QtWidgets.QLabel(self.formLayoutWidget)
        self.hcRunsLabel.setObjectName("hcRunsLabel")
        self.formLayout.setWidget(1, QtWidgets.QFormLayout.LabelRole, self.hcRunsLabel)
        self.hcRunsInput = QtWidgets.QSpinBox(self.formLayoutWidget)
        self.hcRunsInput.setMaximumSize(QtCore.QSize(300, 16777215))
        self.hcRunsInput.setMinimum(1)
        self.hcRunsInput.setMaximum(10000)
        self.hcRunsInput.setSingleStep(100)
        self.hcRunsInput.setProperty("value", 1000)
        self.hcRunsInput.setObjectName("hcRunsInput")
        self.formLayout.setWidget(1, QtWidgets.QFormLayout.FieldRole, self.hcRunsInput)
        self.configTabWidget.addTab(self.climbTab, "")
        self.geneticTab = QtWidgets.QWidget()
        self.geneticTab.setObjectName("geneticTab")
        self.formLayoutWidget_2 = QtWidgets.QWidget(self.geneticTab)
        self.formLayoutWidget_2.setGeometry(QtCore.QRect(0, 0, 451, 631))
        self.formLayoutWidget_2.setObjectName("formLayoutWidget_2")
        self.geneticFormLayout = QtWidgets.QFormLayout(self.formLayoutWidget_2)
        self.geneticFormLayout.setLabelAlignment(QtCore.Qt.AlignLeading|QtCore.Qt.AlignLeft|QtCore.Qt.AlignVCenter)
        self.geneticFormLayout.setFormAlignment(QtCore.Qt.AlignLeading|QtCore.Qt.AlignLeft|QtCore.Qt.AlignVCenter)
        self.geneticFormLayout.setContentsMargins(0, 0, 0, 0)
        self.geneticFormLayout.setObjectName("geneticFormLayout")
        self.geneticNLabel = QtWidgets.QLabel(self.formLayoutWidget_2)
        self.geneticNLabel.setObjectName("geneticNLabel")
        self.geneticFormLayout.setWidget(0, QtWidgets.QFormLayout.LabelRole, self.geneticNLabel)
        self.geneticPopSizeLabel = QtWidgets.QLabel(self.formLayoutWidget_2)
        self.geneticPopSizeLabel.setObjectName("geneticPopSizeLabel")
        self.geneticFormLayout.setWidget(1, QtWidgets.QFormLayout.LabelRole, self.geneticPopSizeLabel)
        self.geneticPopReplaceLabel = QtWidgets.QLabel(self.formLayoutWidget_2)
        self.geneticPopReplaceLabel.setObjectName("geneticPopReplaceLabel")
        self.geneticFormLayout.setWidget(2, QtWidgets.QFormLayout.LabelRole, self.geneticPopReplaceLabel)
        self.geneticTournamentSizeLabel = QtWidgets.QLabel(self.formLayoutWidget_2)
        self.geneticTournamentSizeLabel.setObjectName("geneticTournamentSizeLabel")
        self.geneticFormLayout.setWidget(3, QtWidgets.QFormLayout.LabelRole, self.geneticTournamentSizeLabel)
        self.geneticRunsLabel = QtWidgets.QLabel(self.formLayoutWidget_2)
        self.geneticRunsLabel.setObjectName("geneticRunsLabel")
        self.geneticFormLayout.setWidget(4, QtWidgets.QFormLayout.LabelRole, self.geneticRunsLabel)
        self.geneticMutationSizeLabel = QtWidgets.QLabel(self.formLayoutWidget_2)
        self.geneticMutationSizeLabel.setObjectName("geneticMutationSizeLabel")
        self.geneticFormLayout.setWidget(5, QtWidgets.QFormLayout.LabelRole, self.geneticMutationSizeLabel)
        self.geneticNInput = QtWidgets.QSpinBox(self.formLayoutWidget_2)
        self.geneticNInput.setMaximumSize(QtCore.QSize(300, 16777215))
        self.geneticNInput.setMinimum(2)
        self.geneticNInput.setMaximum(10)
        self.geneticNInput.setObjectName("geneticNInput")
        self.geneticFormLayout.setWidget(0, QtWidgets.QFormLayout.FieldRole, self.geneticNInput)
        self.geneticPopSizeInput = QtWidgets.QSpinBox(self.formLayoutWidget_2)
        self.geneticPopSizeInput.setMaximumSize(QtCore.QSize(300, 16777215))
        self.geneticPopSizeInput.setMinimum(10)
        self.geneticPopSizeInput.setMaximum(10000)
        self.geneticPopSizeInput.setSingleStep(5)
        self.geneticPopSizeInput.setProperty("value", 50)
        self.geneticPopSizeInput.setObjectName("geneticPopSizeInput")
        self.geneticFormLayout.setWidget(1, QtWidgets.QFormLayout.FieldRole, self.geneticPopSizeInput)
        self.geneticPopReplaceInput = QtWidgets.QSpinBox(self.formLayoutWidget_2)
        self.geneticPopReplaceInput.setMaximumSize(QtCore.QSize(300, 16777215))
        self.geneticPopReplaceInput.setMinimum(10)
        self.geneticPopReplaceInput.setMaximum(10000)
        self.geneticPopReplaceInput.setObjectName("geneticPopReplaceInput")
        self.geneticFormLayout.setWidget(2, QtWidgets.QFormLayout.FieldRole, self.geneticPopReplaceInput)
        self.geneticTournamentSizeInput = QtWidgets.QSpinBox(self.formLayoutWidget_2)
        self.geneticTournamentSizeInput.setMaximumSize(QtCore.QSize(300, 16777215))
        self.geneticTournamentSizeInput.setMinimum(1)
        self.geneticTournamentSizeInput.setMaximum(10000)
        self.geneticTournamentSizeInput.setSingleStep(1)
        self.geneticTournamentSizeInput.setObjectName("geneticTournamentSizeInput")
        self.geneticFormLayout.setWidget(3, QtWidgets.QFormLayout.FieldRole, self.geneticTournamentSizeInput)
        self.geneticRunsInput = QtWidgets.QSpinBox(self.formLayoutWidget_2)
        self.geneticRunsInput.setMaximumSize(QtCore.QSize(300, 16777215))
        self.geneticRunsInput.setMinimum(1)
        self.geneticRunsInput.setMaximum(10000)
        self.geneticRunsInput.setSingleStep(100)
        self.geneticRunsInput.setProperty("value", 1000)
        self.geneticRunsInput.setObjectName("geneticRunsInput")
        self.geneticFormLayout.setWidget(4, QtWidgets.QFormLayout.FieldRole, self.geneticRunsInput)
        self.geneticMutationChanceInput = QtWidgets.QDoubleSpinBox(self.formLayoutWidget_2)
        self.geneticMutationChanceInput.setMaximumSize(QtCore.QSize(300, 16777215))
        self.geneticMutationChanceInput.setMaximum(1.0)
        self.geneticMutationChanceInput.setSingleStep(0.05)
        self.geneticMutationChanceInput.setProperty("value", 0.3)
        self.geneticMutationChanceInput.setObjectName("geneticMutationChanceInput")
        self.geneticFormLayout.setWidget(5, QtWidgets.QFormLayout.FieldRole, self.geneticMutationChanceInput)
        self.configTabWidget.addTab(self.geneticTab, "")
        self.psoTab = QtWidgets.QWidget()
        self.psoTab.setObjectName("psoTab")
        self.formLayoutWidget_4 = QtWidgets.QWidget(self.psoTab)
        self.formLayoutWidget_4.setGeometry(QtCore.QRect(0, 0, 451, 631))
        self.formLayoutWidget_4.setObjectName("formLayoutWidget_4")
        self.psoFormLayout = QtWidgets.QFormLayout(self.formLayoutWidget_4)
        self.psoFormLayout.setLabelAlignment(QtCore.Qt.AlignCenter)
        self.psoFormLayout.setFormAlignment(QtCore.Qt.AlignLeading|QtCore.Qt.AlignLeft|QtCore.Qt.AlignVCenter)
        self.psoFormLayout.setContentsMargins(0, 0, 0, 0)
        self.psoFormLayout.setObjectName("psoFormLayout")
        self.psoNLabel = QtWidgets.QLabel(self.formLayoutWidget_4)
        self.psoNLabel.setObjectName("psoNLabel")
        self.psoFormLayout.setWidget(0, QtWidgets.QFormLayout.LabelRole, self.psoNLabel)
        self.psoNInput = QtWidgets.QSpinBox(self.formLayoutWidget_4)
        self.psoNInput.setMinimumSize(QtCore.QSize(100, 0))
        self.psoNInput.setMaximumSize(QtCore.QSize(300, 16777215))
        self.psoNInput.setMinimum(2)
        self.psoNInput.setMaximum(10)
        self.psoNInput.setProperty("value", 3)
        self.psoNInput.setObjectName("psoNInput")
        self.psoFormLayout.setWidget(0, QtWidgets.QFormLayout.FieldRole, self.psoNInput)
        self.psoRunsLabel = QtWidgets.QLabel(self.formLayoutWidget_4)
        self.psoRunsLabel.setObjectName("psoRunsLabel")
        self.psoFormLayout.setWidget(1, QtWidgets.QFormLayout.LabelRole, self.psoRunsLabel)
        self.psoRunsInput = QtWidgets.QSpinBox(self.formLayoutWidget_4)
        self.psoRunsInput.setMaximumSize(QtCore.QSize(300, 16777215))
        self.psoRunsInput.setMinimum(1)
        self.psoRunsInput.setMaximum(10000)
        self.psoRunsInput.setProperty("value", 99)
        self.psoRunsInput.setObjectName("psoRunsInput")
        self.psoFormLayout.setWidget(1, QtWidgets.QFormLayout.FieldRole, self.psoRunsInput)
        self.psoSwarmSizeLabel = QtWidgets.QLabel(self.formLayoutWidget_4)
        self.psoSwarmSizeLabel.setObjectName("psoSwarmSizeLabel")
        self.psoFormLayout.setWidget(2, QtWidgets.QFormLayout.LabelRole, self.psoSwarmSizeLabel)
        self.psoSwarmSizeInput = QtWidgets.QSpinBox(self.formLayoutWidget_4)
        self.psoSwarmSizeInput.setMaximumSize(QtCore.QSize(300, 16777215))
        self.psoSwarmSizeInput.setMinimum(2)
        self.psoSwarmSizeInput.setMaximum(10000)
        self.psoSwarmSizeInput.setSingleStep(1)
        self.psoSwarmSizeInput.setProperty("value", 1000)
        self.psoSwarmSizeInput.setObjectName("psoSwarmSizeInput")
        self.psoFormLayout.setWidget(2, QtWidgets.QFormLayout.FieldRole, self.psoSwarmSizeInput)
        self.psoWLabel = QtWidgets.QLabel(self.formLayoutWidget_4)
        self.psoWLabel.setObjectName("psoWLabel")
        self.psoFormLayout.setWidget(3, QtWidgets.QFormLayout.LabelRole, self.psoWLabel)
        self.psoWInput = QtWidgets.QDoubleSpinBox(self.formLayoutWidget_4)
        self.psoWInput.setMaximumSize(QtCore.QSize(300, 16777215))
        self.psoWInput.setMaximum(1.0)
        self.psoWInput.setSingleStep(0.05)
        self.psoWInput.setProperty("value", 0.3)
        self.psoWInput.setObjectName("psoWInput")
        self.psoFormLayout.setWidget(3, QtWidgets.QFormLayout.FieldRole, self.psoWInput)
        self.psoC1Label = QtWidgets.QLabel(self.formLayoutWidget_4)
        self.psoC1Label.setObjectName("psoC1Label")
        self.psoFormLayout.setWidget(4, QtWidgets.QFormLayout.LabelRole, self.psoC1Label)
        self.psoC1Input = QtWidgets.QDoubleSpinBox(self.formLayoutWidget_4)
        self.psoC1Input.setMaximumSize(QtCore.QSize(300, 16777215))
        self.psoC1Input.setMaximum(1.0)
        self.psoC1Input.setSingleStep(0.05)
        self.psoC1Input.setProperty("value", 0.2)
        self.psoC1Input.setObjectName("psoC1Input")
        self.psoFormLayout.setWidget(4, QtWidgets.QFormLayout.FieldRole, self.psoC1Input)
        self.psoC2Label = QtWidgets.QLabel(self.formLayoutWidget_4)
        self.psoC2Label.setObjectName("psoC2Label")
        self.psoFormLayout.setWidget(5, QtWidgets.QFormLayout.LabelRole, self.psoC2Label)
        self.psoC2Input = QtWidgets.QDoubleSpinBox(self.formLayoutWidget_4)
        self.psoC2Input.setMaximumSize(QtCore.QSize(300, 16777215))
        self.psoC2Input.setMaximum(1.0)
        self.psoC2Input.setSingleStep(0.05)
        self.psoC2Input.setProperty("value", 0.5)
        self.psoC2Input.setObjectName("psoC2Input")
        self.psoFormLayout.setWidget(5, QtWidgets.QFormLayout.FieldRole, self.psoC2Input)
        self.configTabWidget.addTab(self.psoTab, "")
        self.configLayout.addWidget(self.configTabWidget)
        self.verticalLayout_2 = QtWidgets.QVBoxLayout()
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.configLayout.addLayout(self.verticalLayout_2)
        spacerItem1 = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.configLayout.addItem(spacerItem1)
        self.resultsButtonsLayout = QtWidgets.QVBoxLayout()
        self.resultsButtonsLayout.setObjectName("resultsButtonsLayout")
        spacerItem2 = QtWidgets.QSpacerItem(20, 40, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Expanding)
        self.resultsButtonsLayout.addItem(spacerItem2)
        self.resultsLayout = QtWidgets.QVBoxLayout()
        self.resultsLayout.setObjectName("resultsLayout")
        spacerItem3 = QtWidgets.QSpacerItem(20, 40, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Expanding)
        self.resultsLayout.addItem(spacerItem3)
        self.resultPlot = QtWidgets.QLabel()
        self.resultPlot.setWordWrap(True)
        self.resultPlot.setObjectName("resultPlot")
        self.resultsLayout.addWidget(self.resultPlot)
        spacerItem4 = QtWidgets.QSpacerItem(20, 40, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Expanding)
        self.resultsLayout.addItem(spacerItem4)
        self.fitnessPlot = FigureCanvas(Figure(figsize=(5,5)))
        self.fitnessPlot.setMinimumSize(QtCore.QSize(1200, 300))
        self.fitnessPlot.setObjectName("fitnessPlot")
        self.resultsLayout.addWidget(self.fitnessPlot)
        spacerItem5 = QtWidgets.QSpacerItem(20, 40, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Expanding)
        self.resultsLayout.addItem(spacerItem5)
        self.fitnessStatsLayout = QtWidgets.QFormLayout()
        self.fitnessStatsLayout.setObjectName("fitnessStatsLayout")
        self.averageLabel = QtWidgets.QLabel(self.horizontalLayoutWidget_2)
        self.averageLabel.setObjectName("averageLabel")
        self.fitnessStatsLayout.setWidget(0, QtWidgets.QFormLayout.LabelRole, self.averageLabel)
        self.averageValueLabel = QtWidgets.QLabel(self.horizontalLayoutWidget_2)
        self.averageValueLabel.setAlignment(QtCore.Qt.AlignCenter)
        self.averageValueLabel.setObjectName("averageValueLabel")
        self.fitnessStatsLayout.setWidget(0, QtWidgets.QFormLayout.FieldRole, self.averageValueLabel)
        self.medianLabel = QtWidgets.QLabel(self.horizontalLayoutWidget_2)
        self.medianLabel.setObjectName("medianLabel")
        self.fitnessStatsLayout.setWidget(1, QtWidgets.QFormLayout.LabelRole, self.medianLabel)
        self.medianValueLabel = QtWidgets.QLabel(self.horizontalLayoutWidget_2)
        self.medianValueLabel.setAlignment(QtCore.Qt.AlignCenter)
        self.medianValueLabel.setObjectName("medianValueLabel")
        self.fitnessStatsLayout.setWidget(1, QtWidgets.QFormLayout.FieldRole, self.medianValueLabel)
        self.resultsLayout.addLayout(self.fitnessStatsLayout)
        spacerItem6 = QtWidgets.QSpacerItem(20, 40, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Expanding)
        self.resultsLayout.addItem(spacerItem6)
        self.resultsButtonsLayout.addLayout(self.resultsLayout)
        spacerItem7 = QtWidgets.QSpacerItem(20, 40, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Expanding)
        self.resultsButtonsLayout.addItem(spacerItem7)
        self.buttonsLayout = QtWidgets.QHBoxLayout()
        self.buttonsLayout.setObjectName("buttonsLayout")
        spacerItem8 = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.buttonsLayout.addItem(spacerItem8)
        self.resetValuesButton = QtWidgets.QPushButton(self.horizontalLayoutWidget_2)
        self.resetValuesButton.setObjectName("resetValuesButton")
        self.buttonsLayout.addWidget(self.resetValuesButton)
        spacerItem9 = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.buttonsLayout.addItem(spacerItem9)
        self.calculateButton = QtWidgets.QPushButton(self.horizontalLayoutWidget_2)
        self.calculateButton.setObjectName("calculateButton")
        self.buttonsLayout.addWidget(self.calculateButton)
        spacerItem10 = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.buttonsLayout.addItem(spacerItem10)
        self.resultsButtonsLayout.addLayout(self.buttonsLayout)
        self.configLayout.addLayout(self.resultsButtonsLayout)
        spacerItem11 = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.configLayout.addItem(spacerItem11)
        MainWindow.setCentralWidget(self.centralwidget)

        self.calculateButton.clicked.connect(self._calculate_button_clicked)
        self.resetValuesButton.clicked.connect(self._reset_parameters)

        self.retranslateUi(MainWindow)
        self.configTabWidget.setCurrentIndex(2)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "CaterincaAI"))
        self.climbTab.setToolTip(_translate("MainWindow", "<html><head/><body><p><br/></p></body></html>"))
        self.hcNLabel.setText(_translate("MainWindow", "n"))
        self.hcRunsLabel.setText(_translate("MainWindow", "runs"))
        self.configTabWidget.setTabText(self.configTabWidget.indexOf(self.climbTab), _translate("MainWindow", "Hill Climb"))
        self.geneticNLabel.setText(_translate("MainWindow", "n"))
        self.geneticPopSizeLabel.setText(_translate("MainWindow", "pop_size"))
        self.geneticPopReplaceLabel.setText(_translate("MainWindow", "pop_replace"))
        self.geneticTournamentSizeLabel.setText(_translate("MainWindow", "tournament_size"))
        self.geneticRunsLabel.setText(_translate("MainWindow", "runs"))
        self.geneticMutationSizeLabel.setText(_translate("MainWindow", "mutation_chance"))
        self.configTabWidget.setTabText(self.configTabWidget.indexOf(self.geneticTab), _translate("MainWindow", "Genetic"))
        self.psoNLabel.setText(_translate("MainWindow", "n"))
        self.psoRunsLabel.setText(_translate("MainWindow", "runs"))
        self.psoSwarmSizeLabel.setText(_translate("MainWindow", "swarm_size"))
        self.psoWLabel.setText(_translate("MainWindow", "w"))
        self.psoC1Label.setText(_translate("MainWindow", "c1"))
        self.psoC2Label.setText(_translate("MainWindow", "c2"))
        self.configTabWidget.setTabText(self.configTabWidget.indexOf(self.psoTab), _translate("MainWindow", "PSO"))
        self.averageLabel.setText(_translate("MainWindow", "Average Validation Fitness"))
        self.averageValueLabel.setText(_translate("MainWindow", "N/A"))
        self.medianLabel.setText(_translate("MainWindow", "Median Validation Fitness"))
        self.medianValueLabel.setText(_translate("MainWindow", "N/A"))
        self.resetValuesButton.setText(_translate("MainWindow", "Reset"))
        self.calculateButton.setText(_translate("MainWindow", " Calculate"))