# import tkMessageBox
# from Tkinter import *
import tkinter as tk
from tkinter import *
import time
from tkinter import messagebox
from tkinter.filedialog import askopenfilename
import numpy as np
import tkinter.filedialog
import csv
import matplotlib.pyplot as plt
import matplotlib.animation as animation
#
# min_start = {}
# min_end = {}
# max_start = {}
# duration = {}
# max_end = {}
# slack = {}
# high ={}
# class Window:
#
#  def __init__(self, master):
#     self.filename=""
#     # bar=Entry(master).grid(row=1, column=1)
#     #Buttons
#     y=7
#     self.cbutton= Button(root, text="")
#     y+=1
#     self.cbutton.grid(row=10, column=3, sticky = W + E)
#     self.bbutton= Button(root, text="Browse", command=self.browsecsv)
#     self.bbutton.grid(row=1, column=3)
#
#  def browsecsv(self):
#
#     self.filename = askopenfilename()
#     print(self.filename)
#     index = self.filename.find('.csv')
#     print (index)
#     if index != -1:
#         print("cool")
#     else :
#         messagebox.showerror("Error", "Wrong File Format")
#
#
# root = tk.Tk()
# root.title("PERT CHART")
# window=Window(root)
# root.mainloop()

# The code for changing pages was derived from: http://stackoverflow.com/questions/7546050/switch-between-two-frames-in-tkinter
# License: http://creativecommons.org/licenses/by-sa/3.0/

import matplotlib

matplotlib.use("TkAgg")
from matplotlib.backends.backend_tkagg import *
from matplotlib.figure import Figure

import tkinter as tk
from tkinter import ttk

LARGE_FONT = ("Verdana", 12)

class SeaofBTCapp(tk.Tk):

    def __init__(self, *args, **kwargs):
        tk.Tk.__init__(self, *args, **kwargs)

        # tk.Tk.iconbitmap(self, default="clienticon.ico")
        tk.Tk.wm_title(self, "Segmented Least Squares")

        container = tk.Frame(self)
        container.pack(side="top", fill="both", expand=True)
        container.grid_rowconfigure(0, weight=1)
        container.grid_columnconfigure(0, weight=1)

        self.frames = {}

        frame = PageThree(container, self)

        self.frames[PageThree] = frame

        frame.grid(row=0, column=0, sticky="nsew")

        self.show_frame(PageThree)

    def show_frame(self, cont):
        frame = self.frames[cont]
        frame.tkraise()

    def browsecsv(self):

        self.filename = askopenfilename()
        print(self.filename)
        index = self.filename.find('.csv')
        print (index)
        if index != -1:
            print("cool")
        else :
            messagebox.showerror("Error", "Wrong File Format")
class StartPage(tk.Frame):

    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)
        label = tk.Label(self, text="Start Page", font=LARGE_FONT)
        label.pack(pady=10, padx=10)

        button = ttk.Button(self, text="Visit Page 1",
                            command=lambda: controller.show_frame(PageOne))
        button.pack()

        button2 = ttk.Button(self, text="Visit Page 2",
                             command=lambda: controller.show_frame(PageTwo))
        button2.pack()

        button3 = ttk.Button(self, text="Graph Page",
                             command=lambda: controller.show_frame(PageThree))
        button3.pack()


class PageOne(tk.Frame):

    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)
        label = tk.Label(self, text="Page One!!!", font=LARGE_FONT)
        label.pack(pady=10, padx=10)

        button1 = ttk.Button(self, text="Back to Home",
                             command=lambda: controller.show_frame(StartPage))
        button1.pack()

        button2 = ttk.Button(self, text="Page Two",
                             command=lambda: controller.show_frame(PageTwo))
        button2.pack()


class PageTwo(tk.Frame):

    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)
        label = tk.Label(self, text="Page Two!!!", font=LARGE_FONT)
        label.pack(pady=10, padx=10)

        button1 = ttk.Button(self, text="Back to Home",
                             command=lambda: controller.show_frame(StartPage))
        button1.pack()

        button2 = ttk.Button(self, text="Page One",
                             command=lambda: controller.show_frame(PageOne))
        button2.pack()
filename = 'empty.csv'

class PageThree(tk.Frame):

    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)

        self.filename="ok"
        self.var=IntVar(0)
        # print (filename)
        label = tk.Label(self, text="Segmented Least Squares", font=LARGE_FONT)
        label.pack(pady=10, padx=10)

        button1 = ttk.Button(self, text="browse",
                             command=self.browsecsv)

        button1.pack()


        button = Button(self, text="Get Cost Value", command=self.sel)
        button.pack(anchor=CENTER)
        scale = Scale(self, orient=HORIZONTAL,variable=self.var)
        scale.pack()
        button2 = ttk.Button(self, text="Calculate segments",
                             command=self.Line_Seg)
        button2.pack()



        self.label = Label(self)
        self.label.pack()

        self.f = Figure(figsize=(5, 5), dpi=100)
        self.a = (self.f).add_subplot(111)
        self.canvas = FigureCanvasTkAgg(self.f)
        self.canvas.get_tk_widget().pack(side=tk.BOTTOM, fill=tk.BOTH, expand=True)

    def sel(self):
        selection = "Value = " + str(self.var.get())
        self.label.config(text=selection)

    def browsecsv(self):
        print('x')
        self.filename = askopenfilename()
        print(self.filename)
        index = self.filename.find('.csv')
        print (index)
        if index != -1:
            it=self.filename.rfind('/')
            self.filename=self.filename[it+1:]
            print(filename)

        else :
            messagebox.showerror("Error", "Wrong File Format")

    def Line_Seg(self):
        import os
        os.system("g++ daa_2.cpp  -o main")
        os.system("./main "+str(self.var.get())+" "+self.filename)
        print(self.filename)
        print('ok')
        data = np.loadtxt(self.filename, dtype='double,double', delimiter=',', usecols=(0, 1), unpack=True)
        xs = data[0]
        ys = data[1]

        # or x in range(len(xs)):
        self.a.clear()
        self.a.axis([-10, 10, -10, 10])
        self.a.plot(xs, ys, 'ro')

        data2 = np.loadtxt('output.csv', dtype='double,double', delimiter=',', usecols=(0, 1), unpack=True)
        xs2 = data2[0]
        ys2 = data2[1]
        for i in np.arange(0, len(xs2), 2):
            (self.a).plot(xs2[i:i + 2], ys2[i:i + 2], 'ro-')
        self.canvas.draw()



app = SeaofBTCapp()
app.mainloop()
