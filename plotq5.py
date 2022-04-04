import matplotlib.pyplot as plt

omp=[0.126581,0.192488,0.287561,0.382411,0.480962,0.572804,0.668217,0.762894,0.861398,0.953938,1.048717,1.143758,1.339465,1.333316,1.428976,1.524926,1.619636,1.714148,1.810174,1.904644,2.000373,2.094152,2.191079,2.284829,2.382250,2.476750,2.570172,2.665226,2.759919,2.855484,2.950578,3.045593,3.138806,3.234348,3.330790]

task=[0.000000,0.080989,0.118954,0.155150,0.197610,0.237229,0.279521,0.313627,0.348698,0.388566,0.432958,0.472196,0.508236,0.540672,0.583822,0.634047,0.662824,0.706379,0.744023,0.786404,0.831772,0.911066,0.976286,1.005586,1.009231,1.150163,1.173473,1.202830,1.175928,1.190001,1.323000,1.333944,1.423982,1.382436,1.393269,1.420596,1.464607,1.518562,1.522606,1.576721,1.587864,1.636151,1.678898,1.716195,1.753340,1.790781,1.829383,1.894053,1.937167,1.993654,2.072778,2.121129,2.085742,2.122012,2.141443]

serial=[0.276284,0.477127,0.713318,0.950548,1.204087,1.467657,1.741856,2.016881,2.123575,2.359091,2.593872,2.829646,3.062624,3.299500,3.534153,3.768670,4.010130,4.248092,4.473689,4.709260,4.943375,5.184967]

iteration=[1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,11000,12000,13000,14000,15000,16000,17000,18000,19000,20000,21000,22000,23000,24000,25000,26000,27000,28000,29000,30000,31000,32000,33000,34000,35000,36000,37000,38000,39000,40000,41000,42000,43000,44000,45000,46000,47000,48000,49000,50000,51000,52000,53000,54000,55000]

iterationOMP = [1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,11000,12000,13000,14000,15000,16000,17000,18000,19000,20000,21000,22000,23000,24000,25000,26000,27000,28000,29000,30000,31000,32000,33000,34000,35000]

iterationSerial = [1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,11000,12000,13000,14000,15000,16000,17000,18000,19000,20000,21000,22000]

plt.xlabel("iterations")
plt.ylabel("time in seconds")
plt.plot(iterationOMP,omp,label="omp")
plt.plot(iteration,task,label="task")
plt.plot(iterationSerial,serial,label="serial")
plt.legend()
plt.title("Local Machine")
plt.show()