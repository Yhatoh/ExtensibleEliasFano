import random

testCases = 1
bitLimit = 100000000
probabilities = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
run = [2048, 4096, 8192]

random.seed(201573140)
#randomRuns
for test in range(testCases):
  for runSize in run:
    for probabilitie in probabilities:

      testFile = open(f'./randomRuns/z{runSize}o{runSize}p{probabilitie}t{test}.txt', 'w')
      testFile.write(f'{bitLimit}\n')
      remainingBits = bitLimit
      bitsCount = 0
      onesCount = 0

      while remainingBits > 0:

        randZeros = random.randint(1, runSize)

        if (randZeros > remainingBits):
          randZeros = remainingBits - 1
        remainingBits -= randZeros + 1

        for i in range(randZeros):
          testFile.write('0')
          bitsCount += 1

        testFile.write('1')
        bitsCount += 1
        onesCount += 1
        
        randOnes = 0
        randResult = random.randint(1, 1000)
        if randResult <= probabilitie:
          randOnes = random.randint(1, runSize)
        if randOnes > remainingBits:
          randOnes = remainingBits
        remainingBits -= randOnes
        for i in range(randOnes):
          testFile.write('1')
          bitsCount += 1
          onesCount += 1
      testFile.close()
      print(f'./randomRuns/z{runSize}o{runSize}p{probabilitie}t{test}.txt')