# sht11-linkItOne-mcs
uploading the data from sht sensor to cloud fromLinkIt One board.

This repository consists of the main file which measures temperature and reative humidity from the environment and uploads the data on the Mediatek Cloud Sandbox.
I have used my own library of SHT1x sensor which i have uploaded earlier.
So in order for your code to work you need to download this repository.
Here I have written two functons :-
1. upload_to_cloud_temp()
2. upload_to_cloud_hum()
which are responsible for uploading the data on the cloud of temperature and humidity respectively.

I am uploading the data every 5 sec you can change the upload time by changing the feild in delay();
note that tis feild is in micro seconds.
So for a 5 sec delay you have to write delay(5000);
