import sys
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QLabel, QLineEdit
from PyQt5.QtGui import QIcon
from PyQt5.QtCore import pyqtSlot

class App(QWidget):

    def __init__(self):
        super().__init__()
        self.title = 'GUI for goals'
        self.left = 10
        self.top = 10
        self.width = 320
        self.height = 200
        # self.initUI()
        self.UiComponents()
        self.show()
    
    # def initUI(self):
    #     self.setWindowTitle(self.title)
    #     self.setGeometry(self.left, self.top, self.width, self.height)

    #     button_goal = QPushButton('Send goal', self)
    #     button_goal.setToolTip('Click to send the goal')
    #     button_goal.move(40,160)
    #     button_goal.clicked.connect(self.goal_click)
        
    #     button_cancel = QPushButton('Cancel goal', self)
    #     button_cancel.setToolTip('Click to cancel the goal')
    #     button_cancel.move(200,160)
    #     button_cancel.clicked.connect(self.cancel_click)


    # @pyqtSlot()
    # def goal_click(self):
    #     print('Goal sent!')

    # def cancel_click(self):
    #     print('Goal cancelled!')


# method for components
    def UiComponents(self):

        self.setWindowTitle(self.title)
        self.setGeometry(self.left, self.top, self.width, self.height)

        button_goal = QPushButton('Send goal', self)
        button_goal.setToolTip('Click to send the goal')
        button_goal.move(40,160)
        button_goal.clicked.connect(lambda: goal_click())
        
        button_cancel = QPushButton('Cancel goal', self)
        button_cancel.setToolTip('Click to cancel the goal')
        button_cancel.move(200,160)
        button_cancel.clicked.connect(lambda: cancel_click())

        # creating a QLineEdit object
        line_x = QLineEdit(" ", self)
        # setting geometry
        line_x.setGeometry(200, 20, 100, 30)
        # creating a label
        label_x = QLabel("Introduce x position goal: ", self)
        # setting geometry to the label
        label_x.setGeometry(20, 20, 200, 40)
        # setting word wrap property of label
        label_x.setWordWrap(True)
        # adding action to the line edit when enter key is pressed
        line_x.returnPressed.connect(lambda: x_postition())

        # creating a QLineEdit object
        line_y = QLineEdit(" ", self)
        # setting geometry
        line_y.setGeometry(200, 60, 100, 30)
        # creating a label
        label_y = QLabel("Introduce y position goal: ", self)
        # setting geometry to the label
        label_y.setGeometry(20, 60, 200, 40)
        # setting word wrap property of label
        label_y.setWordWrap(True)
        # adding action to the line edit when enter key is pressed
        line_y.returnPressed.connect(lambda: y_postition())


        # method to do action
        def x_postition():
            # getting text from the line edit
            value = line_x.text()
            print(value)

        # method to do action
        def y_postition():
            # getting text from the line edit
            value = line_y.text()
            print(value)

        def goal_click():
            print('Goal sent!')
            print(line_x.text(), line_y.text())

        def cancel_click():
            print('Goal cancelled!')

if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = App()
    sys.exit(app.exec_())