label1:

label2:		beq x1,x2, lable2
		bne x2, x3, label1
label3:		jal x0, label2
		bne x3, x4, label1
			
label4:		jal x0, label1

		beq x1, x2, label2
