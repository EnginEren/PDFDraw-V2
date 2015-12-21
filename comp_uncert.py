import math, sys, time, subprocess
from subprocess import Popen, PIPE
from shlex import split


# Check that the script is called with arguments
if len(sys.argv) < 3:
    sys.stderr.write('not enough parameter!\n')
    sys.stderr.write('Run like this : python comp_uncert.py hera+cms gluon!\n')
    sys.exit(1)

experiment=sys.argv[1]             #determine the experiment, (hera or hera+cms)
flavor=sys.argv[2]                 #determine the flavor, (up, down and gluon)

#Function for writing lists in to a txt file

def writeTo(filename, data):
    with open(filename, 'w') as f:
        for i in data:
            f.write(str(i))
            f.write('\n')

#function for combining files
def combine(f,exp, typ):
    if typ == "exp":
        combine = "paste -d ' ' store/central-x store/"+ f +  "_01-central-" + exp + " store/"+f + "plus store/" + f + "minus"
        arrange = "awk '{print $1,$2,($2+$3), ($2-$4)}' > store/" + f + "-EXP-" + exp
    elif typ == "exp+mod":
        combine = "paste -d ' ' store/central-x store/"+ f +  "_01-central-" + exp + " store/"+ f + "Exp+Mod-plus store/" + f + "Exp+Mod-minus"
        arrange = "awk '{print $1,$2,($2+$3), ($2-$4)}' > store/" + f + "-EXP+MOD-" + exp

    p1 = Popen(combine, stdout=PIPE, shell=True)
    p2 = Popen(arrange, stdin=p1.stdout, shell=True)

    p1.wait()
    p2.wait()

    #print "File : store/" + f + "-EXP-" + exp + '\n'
    #print "File : store/" + f + "-EXP+MOD-" + exp + '\n'
    #print "created.."


# Function for "adding in quadrature"
def addinQ(x):
    sq = 0.000
    for j in x :
        sq += pow(j,2)
    return math.sqrt(sq)

# Function for "relative-uncertainty"

def relative(src,output):
    with open(output, 'w') as g:
        with open(src, 'r') as f:
            for i in f:
                nums = i.split()
                c = float(nums[1])
                plus = float(nums[2])
                minus = float(nums[3])
                RelPlus = abs(((plus-c) / c))
                RelNeg  = (-1.0) * abs(((c-minus) / c))
                g.write(nums[0] + ' ')
                g.write(str(c) + ' ')
                g.write(str(RelPlus)+ ' ')
                g.write(str(RelNeg) + ' ')
                g.write('\n')
    g.close()


#Function for experimental uncertatiny calculation
def ForExp(source, plus, minus):
    source = "store/" + source
    with open(source) as f:
        for i in f:
            nums = i.split()
            cent = float(nums[1])
            up = float(nums[2])
            down = float(nums[3])
            plus.append(max(cent,up,down)-cent)
            minus.append(cent - min(cent,up,down))

#Function for model uncertatiny calculation

def ForMod(source, mplus, mminus):
    source = "store/" + source
    with open(source) as f:
        for i in f:
            nums = i.split()
            cent = float(nums[1])
            up = float(nums[2])
            down = float(nums[3])
            mplus.append(max(cent,up,down)-cent)
            mminus.append(cent - min(cent,up,down))

#For exp uncertainty
with open("store/list-sources-" + flavor + "-"+ experiment) as f:
    Plist = []
    Mlist = []
    for i in f:
        lp = []
        lm = []
        i = i.replace("\n","");
        ForExp(i,lp,lm)    #Call funtion for each sources for exp uncertainy
        Plist.append(lp);  #It is a nested list for PLUS uncert. [ [ 101 x values],[ 101 x values], .. 18 source ]
        Mlist.append(lm);  #It is a nested list for MINUS uncert. [ [ 101 x values],[ 101 x values], .. 18 source ]

#For model uncert.
with open("store/list-sources-model-" + flavor + "-"+ experiment) as g:
    modelPlist = []
    modelMlist = []
    for j in g:
        Mlp = []
        Mlm = []
        j = j.replace("\n","");
        ForMod(j,Mlp,Mlm)    #Call funtion for each sources for model uncertainy
        modelPlist.append(Mlp);  #It is a nested list for PLUS uncert. [ [ 101 x values],[ 101 x values], .. 8 source ]
        modelMlist.append(Mlm);  #It is a nested list for MINUS uncert. [ [ 101 x values],[ 101 x values], .. 8 source ]


#Add them in quadrature for total EXP uncertainty
ExpPlus = []
ExpMinus = []
for k in range(0,101) :
    tmpP = []
    tmpM = []
    for j in range(0,18):
        tmpP.append(Plist[j][k])
        tmpM.append(Mlist[j][k])
    ExpPlus.append(addinQ(tmpP))
    ExpMinus.append(addinQ(tmpM))

#Add them in quadrature for total MODEL uncertainty
ModelPlus = []
ModelMinus = []
for a in range(0,101) :
    MtmpP = []
    MtmpM = []
    for b in range(0,8):
        MtmpP.append(Plist[b][a])
        MtmpM.append(Mlist[b][a])
    ModelPlus.append(addinQ(MtmpP))
    ModelMinus.append(addinQ(MtmpM))


#Now we need to add EXP and Model in quad
ExpModelPlus = []
ExpModelMinus = []

for c in range(0,101):
    plus = math.sqrt(pow(ModelPlus[c],2) + pow(ExpPlus[c],2))
    minus = math.sqrt(pow(ModelMinus[c],2) + pow(ExpMinus[c],2))
    ExpModelPlus.append(plus)
    ExpModelMinus.append(minus)


#write to file
writeTo('store/'+flavor+'plus', ExpPlus)
writeTo('store/'+flavor+'minus', ExpMinus)

writeTo('store/'+flavor+'Exp+Mod-plus', ExpModelPlus)
writeTo('store/'+flavor+'Exp+Mod-minus', ExpModelMinus)

combine(flavor,experiment,"exp")
combine(flavor,experiment,"exp+mod")


relative("store/"+ flavor + "-EXP-"+ experiment, "store/"+ flavor + "-EXP-relative-" + experiment)
relative("store/"+ flavor + "-EXP+MOD-"+ experiment, "store/"+ flavor + "-EXP+MOD-relative-" + experiment)

