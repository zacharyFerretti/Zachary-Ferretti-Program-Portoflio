import csv, sys, math, numpy as np
from decimal import * 

def Calculate_Number_Of_Labels(Training_File):
	Number_Of_Voters = len(Training_File)
	Number_Of_Questions = len(Training_File[0])-1#Check this it may actually be no minus one.
	Number_Of_Labels = [0,0]
	for i in range(0, Number_Of_Voters):
		if(Training_File[i][Number_Of_Questions] == "Democrat"):
			Number_Of_Labels[0]=Number_Of_Labels[0]+1
		else:
			Number_Of_Labels[1]=Number_Of_Labels[1]+1
	return Number_Of_Labels

def Most_Common_Label(voters):
	Number_Of_Labels = Calculate_Number_Of_Labels(voters)
	
	Label_And_Percent=["" , 0]
	if (Number_Of_Labels[0]>=Number_Of_Labels[1]):
		Label_And_Percent[0] = "Democrat"
		Label_And_Percent[1] = Number_Of_Labels[0] / (Number_Of_Labels[0] + Number_Of_Labels[1])
	else:
		Label_And_Percent[0] = "Republican"
		Label_And_Percent[1] = Number_Of_Labels[1] / (Number_Of_Labels[0] + Number_Of_Labels[1])
	return Label_And_Percent

def All_Have_Same_Label(voters):
	num_Voters = len(voters)
	num_Question = len(voters[0])-1 #Check this it may actually be no minus one.
	first_Label = voters[0][num_Question]
	for i in range(0, num_Voters):
		if (voters[i][num_Question] != first_Label):
			return False
	return True

def Entropy_Calculator(Probability):
	if(Probability == 0 or Probability == 1):
		return 0
	return -1* (Probability * np.log2(Probability) + (1-Probability) * np.log2(1-Probability))

def Goal_Entropy_Calculator(Example_Voters):
	temp = Calculate_Number_Of_Labels(Example_Voters)
	Number_Of_Democrats = temp[0]
	Number_Of_Republicans = temp[1]
	entropyOfGoalAttribute = Entropy_Calculator(Number_Of_Democrats / (Number_Of_Democrats+Number_Of_Republicans))
	return entropyOfGoalAttribute
	
def Remainder_Calculator(Question_Index, Example_Voters):
	temp = Calculate_Number_Of_Labels(Example_Voters)
	Number_Of_Democrats = temp[0]
	Number_Of_Republicans = temp[1]

	Number_Of_Yea_Democrats=0 #P YEA
	Number_Of_Yea_Republicans=0 #N YEA

	Number_Of_Nay_Democrats=0 #P NAY
	Number_Of_Nay_Republicans=0 #N NAY 

	for index in range(0, len(Example_Voters)):
		response = Example_Voters[index][Question_Index] #this should be a string
		if  (response == "Yea"):
			if(Example_Voters[index][len(Example_Voters[0])-1] == "Democrat"):
				Number_Of_Yea_Democrats=Number_Of_Yea_Democrats+1
			else:
				Number_Of_Yea_Republicans=Number_Of_Yea_Republicans+1
		else:	
			if(Example_Voters[index][len(Example_Voters[0])-1] == "Democrat"):
				Number_Of_Nay_Democrats=Number_Of_Nay_Democrats+1
			else:
				Number_Of_Nay_Republicans=Number_Of_Nay_Republicans+1
	
	Yea_Total_Voters=Number_Of_Yea_Democrats+Number_Of_Yea_Republicans
	Nay_Total_Voters=Number_Of_Nay_Democrats+Number_Of_Nay_Republicans
	
	Total_Voters = Yea_Total_Voters + Nay_Total_Voters
	
	alpha=-1
	beta=-1
	if(Number_Of_Yea_Democrats==0):
		alpha=Entropy_Calculator(0)
	else:
		First_Part_Yea = (Yea_Total_Voters / Total_Voters)
		Second_Part_Yea = Entropy_Calculator(Number_Of_Yea_Democrats / Yea_Total_Voters)
		alpha = First_Part_Yea * Second_Part_Yea
	if(Number_Of_Nay_Democrats==0):
		beta=Entropy_Calculator(0)
	else:
		First_Part_Nay = (Nay_Total_Voters / Total_Voters)
		Second_Part_Nay = Entropy_Calculator(Number_Of_Nay_Democrats / Nay_Total_Voters)
		beta =  First_Part_Nay * Second_Part_Nay 
		
	
	return alpha+beta

def Information_Gain_Calculator(Question_Index, Example_Voters):
	Goal_Entropy = Goal_Entropy_Calculator(Example_Voters)
	return Goal_Entropy - Remainder_Calculator(Question_Index, Example_Voters)

def Decision_Tree_Learning(Example_Voters, Questions_To_Consider, Parent_Example_Voter):
	if (len(Example_Voters)==0):
		temp = Most_Common_Label(Parent_Example_Voter)
		return LeafNode(temp[0], temp[1]) 
	
	if(All_Have_Same_Label(Example_Voters)==True):
		
		return LeafNode(Example_Voters[0][len(Example_Voters[0])-1],1)

	if(len(Questions_To_Consider) == 0):
		temp = Most_Common_Label(Example_Voters)
		return LeafNode(temp[0], temp[1])
	
	else:
		Goal_Entropy_Calculator(Example_Voters)
		maxInformationGain = Information_Gain_Calculator(0, Example_Voters)
		bestIndex = 0
		for index in range (1,len(Questions_To_Consider)):
			
			currInformationGain = Information_Gain_Calculator(index, Example_Voters)
			
			if (currInformationGain > maxInformationGain):
				maxInformationGain=currInformationGain
				bestIndex=index
		# questionsToConsiderNew = list.copy(Questions_To_Consider)
		# del questionsToConsiderNew[bestIndex]
		bestAttribute = Questions_To_Consider[bestIndex]
		del Questions_To_Consider[bestIndex]

		Yea_Examples=[]
		Nay_Examples=[]

		for i in range (0,len(Example_Voters)):
			if (Example_Voters[i][bestIndex] == "Yea"):
				Yea_Examples.append(Example_Voters[i])
			else:
				Nay_Examples.append(Example_Voters[i])

		currentNode = InteriorNode(bestAttribute, Decision_Tree_Learning(Yea_Examples, Questions_To_Consider, Example_Voters),
									  Decision_Tree_Learning(Nay_Examples, Questions_To_Consider, Example_Voters))
		return(currentNode)

def Determine_Questions_To_Consider(Array):
	listToReturn = []
	for i in range(0, len(Array[0])-1):
		listToReturn.append(i)
	return listToReturn
	
def Tree_Function(Training_File, Testing_File):
	
	reader = csv.reader(Training_File, delimiter = ',')
	Training_Array = list(reader)
	reader2 = csv.reader(Testing_File, delimiter = ',')
	Testing_Array=list(reader2)
	Questions_To_Consider = Determine_Questions_To_Consider(Training_Array)
	rootNode = Decision_Tree_Learning(Training_Array, Questions_To_Consider, Training_Array)
	Predictions = Determine_Likely_Party(Testing_Array,rootNode)
	Formatted_Print(Predictions,Testing_Array)

def Formatted_Print(thing1, thing2):
	numDem=0
	numRep=0
	for i in range(0,len(thing1)):
		if(thing1[i][0] == "Democrat"):
			numDem=numDem+1
		else:
			numRep=numRep+1
		print(str(thing1[i][0]) + "," + str(thing1[i][1]))
	
def Determine_Likely_Party(voters, rootNode):
	likely_Party =[["",0]for i in range(0,len(voters))]
	
	for i in range(0,len(voters)): #Iterating over all of the voters
		currNode = rootNode
		while(currNode.isLeaf()==False):
			currIndex = currNode.Question_Index
			if(voters[i][currIndex]=="Yea"):
				currNode=currNode.Yea_Children
			else:
				currNode=currNode.Nay_Children
		likely_Party[i][0] = currNode.Label
		likely_Party[i][1] = currNode.Probability

	return likely_Party

class InteriorNode(object):
    Question_Index = 0
    Yea_Children = object 
    Nay_Children = object 
   
    def isLeaf(self):
    	return False
    def __init__(self, index, leftChildNode, rightChildNode): 
        self.Question_Index = index
        self.Yea_Children = leftChildNode 
        self.Nay_Children = rightChildNode

class LeafNode(object):
    Probability=0
    Label=""
    def isLeaf(self):
    	return True
    def __init__(self, label, prob):  
        self.Label = label
        self.Probability = prob

def main():
	Tree_Function(open(sys.argv[1]), open(sys.argv[2]))
	
if __name__ == "__main__":
	main()