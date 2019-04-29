from __future__ import print_function
import socket
import io
import pickle
import os.path
from googleapiclient.discovery import build
from google_auth_oauthlib.flow import InstalledAppFlow
from google.auth.transport.requests import Request
import time
from scipy.misc import imread

HOST = '127.0.0.1'
PORT = 8080

SCOPES = ['https://www.googleapis.com/auth/spreadsheets']
SPREADSHEET_ID = '1DMVAs5eNuc0PRIFq5hKIpOK-VR2zN0Z0x1JjpHn_x0g'

def main():       
	creds = None
	# The file token.pickle stores the user's access and refresh tokens, and is
	# created automatically when the authorization flow completes for the first
	# time.
	if os.path.exists('token.pickle'):
		with open('token.pickle', 'rb') as token:
			creds = pickle.load(token)
	# If there are no (valid) credentials available, let the user log in.
	if not creds or not creds.valid:
		if creds and creds.expired and creds.refresh_token:
			creds.refresh(Request())
		else:
			flow = InstalledAppFlow.from_client_secrets_file(
				'credentials.json', SCOPES)
			creds = flow.run_local_server()
		# Save the credentials for the next run
		with open('token.pickle', 'wb') as token:
			pickle.dump(creds, token)

	service = build('sheets', 'v4', credentials=creds)
	
	s = socket.socket()   
	s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)       
	print("Socket successfully created")
				   
	s.bind((HOST, PORT))         
	print("socket binded to %s" %(PORT)) 
	  
	s.listen(5)      
	print("socket is listening")     

	c = None  
	while True: 
		if not c:
			c, addr = s.accept()
			print('Got connection from', addr)
		 
		face = c.recv(1)
		image = imread("capture.jpg", mode='RGB') 
		
		arr = []
		for row in image:
			temp = []
			for pixel in row:
				temp.append(65536*pixel[0] + 256*pixel[1] + pixel[2])
			arr.append(temp)
			
		print(arr[0][0])

		values = [[int(face)]] + arr
		body = {'values' : values}
		result = service.spreadsheets().values().update(
			spreadsheetId=SPREADSHEET_ID, range='2:152',
			valueInputOption='RAW', body=body).execute()
		time.sleep(1)
		
		result = service.spreadsheets().values().get(
			spreadsheetId=SPREADSHEET_ID, range='A1:A1').execute()
		lock_val = result.get('values', [])
		
		print(lock_val[0][0])
		
		c.send(lock_val[0][0])
	   
if __name__ == '__main__':
    main()
