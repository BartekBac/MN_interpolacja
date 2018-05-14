import matplotlib.pyplot as plt
import pandas as pd

n=[7,8,15,16]
ab=[3,6]
punkty=["opt", "row"]
for i_n in n:
    for i_ab in ab:
        for i_punkty in punkty:
            data=pd.read_csv("C:/Users/Bartek/Desktop/CondaProject/raport_n="+str(i_n)+"_ab=-"+str(i_ab)+str(i_ab)+"_"+str(i_punkty)+".csv")
            plt.plot(data.x, data.y, label="funkcja interpolowana")
            plt.plot(data.x, data.L, label="wielomian Lagrange'a")
            title="n="+str(i_n)+" a=-"+str(i_ab)+" b="+str(i_ab)+" "+str(i_punkty)
            plt.legend(loc='upper right', shadow=True, fancybox=True, title=title).get_frame().set_alpha(0.4)
            plt.savefig("C:/Users/Bartek/Desktop/CondaProject/"+str(title)+".jpg")
            plt.close()