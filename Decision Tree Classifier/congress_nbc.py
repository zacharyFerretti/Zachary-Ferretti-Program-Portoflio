import csv, sys, math
import numpy as np
from decimal import * 

Number_Of_Yeas = [[]]  #This variable and the one below it will be a 
Number_Of_Nays = [[]]	 #2D Array with 2 rows (dem on top and rep on bottom)
					 #With a column for each question indicating the number of 
					 #nay or yea votes for each question given the party

Probability_Voting_Yea = [[]]   #Much like the data structure above this will be a 
					 #2d Array [[len #QSTNS] len 2]
					 
Training_Array = [[]]
Number_Of_Democrats = 0 ; Number_Of_Republicans = 0 ; Number_Of_Voters = 0 ; Number_Of_Questions = 0

Estimated_Voter_Labels = [[]]

def Count_Yeas_And_Nays(file):
	global Number_Of_Yeas, Number_Of_Nays, Number_Of_Democrats, Number_Of_Republicans, Number_Of_Voters, Number_Of_Questions, Training_Array
	reader = csv.reader(file, delimiter = ',')
	Training_Array = list(reader)
	
	
	
	Number_Of_Voters = len(Training_Array)
	Number_Of_Questions = len(Training_Array[0])-1
	
	Number_Of_Yeas = [[0 for j in range (0, Number_Of_Questions)]for i in range(0,2)]
	Number_Of_Nays = [[0 for j in range (0, Number_Of_Questions)]for i in range(0,2)]
	
	
	index = -1
	for i in range(0, Number_Of_Voters):
		if (Training_Array[i][Number_Of_Questions] == "Democrat"):
			Number_Of_Democrats = Number_Of_Democrats + 1
			index = 0
		else:
			Number_Of_Republicans = Number_Of_Republicans + 1 
			index = 1
		
		for j in range(0,Number_Of_Questions):
			if (Training_Array[i][j] == "Yea"):
				Number_Of_Yeas[index][j] = Number_Of_Yeas[index][j]+1
			elif(Training_Array[i][j] == "Nay"):
				Number_Of_Nays[index][j] = Number_Of_Nays[index][j]+1


#This basically adds one ocurence to everything so that if somethinghas never happened before its not a complete disaster.		
def Laplace_Smooth ():
	global Probability_Voting_Yea, Number_Of_Questions, Number_Of_Yeas, Number_Of_Nays
	Probability_Voting_Yea = [[0 for j in range (0, Number_Of_Questions)] for i in range (0,2)]
	for P in range(0,2):
		for Q in range(0,Number_Of_Questions):
			Probability_Voting_Yea[P][Q] = (Number_Of_Yeas[P][Q]+1) / ((Number_Of_Yeas[P][Q]+Number_Of_Nays[P][Q])+(1*Number_Of_Questions))

def Determine_Likely(file):
	global Estimated_Voter_Labels,Number_Of_Questions, Probability_Voting_Yea, Number_Of_Democrats, Number_Of_Republicans
	
	reader = csv.reader(file, delimiter = ',')
	toPredictArray = list(reader)
	
	Number_Of_Voters_To_Predict = len(toPredictArray)
	
	Estimated_Voter_Labels = [[0 for i in range(0,2)] for j in range(0,Number_Of_Voters_To_Predict)]
	
	probDem = Number_Of_Democrats / (Number_Of_Democrats+Number_Of_Republicans)
	probRep = Number_Of_Republicans / (Number_Of_Democrats+Number_Of_Republicans)
	
	for i in range(0, Number_Of_Voters_To_Predict):
		Probability_Given_Democrat = Decimal(1)
		Probability_Given_Republican = Decimal(1)
		for j in range(0,Number_Of_Questions):
			if(toPredictArray[i][j] == "Yea"):
				Probability_Given_Democrat = Decimal(Probability_Given_Democrat) * Decimal(Probability_Voting_Yea[0][j])
				Probability_Given_Republican = Decimal(Probability_Given_Republican) * Decimal(Probability_Voting_Yea[1][j])
			elif(toPredictArray[i][j] == "Nay"):
				Probability_Given_Democrat = Decimal(Probability_Given_Democrat) * Decimal(1-Probability_Voting_Yea[0][j])
				Probability_Given_Republican = Decimal(Probability_Given_Republican) * Decimal(1-Probability_Voting_Yea[1][j])
		Probability_Given_Democrat = Decimal(Probability_Given_Democrat) * Decimal(probDem)
		Probability_Given_Republican = Decimal(Probability_Given_Republican) * Decimal(probRep)
		
		demPrime = Probability_Given_Democrat / (Probability_Given_Democrat+Probability_Given_Republican)
		repPrime = Probability_Given_Republican / (Probability_Given_Democrat+Probability_Given_Republican)
		
		if(demPrime>repPrime):
			Estimated_Voter_Labels[i][0] = "Democrat"
			Estimated_Voter_Labels[i][1] = demPrime
		else:
			Estimated_Voter_Labels[i][0] = "Republican"
			Estimated_Voter_Labels[i][1] = repPrime

def Formatted_Print(thing1):
	global Training_Array
	numDem=0;numRep=0
	for i in range(0,len(thing1)):
		if(thing1[i][0] == "Democrat"):
			numDem=numDem+1
		else:
			numRep=numRep+1
		print(str(thing1[i][0]) + "," + str(thing1[i][1]))
	
def Bayes_Function(trainingFile,testingFile):
	global Estimated_Voter_Labels
	Count_Yeas_And_Nays(trainingFile)
	Laplace_Smooth()
	Determine_Likely(testingFile)
	Formatted_Print(Estimated_Voter_Labels)

def main():
	Bayes_Function(open(sys.argv[1]), open(sys.argv[2]))

if __name__ == "__main__":
	main()