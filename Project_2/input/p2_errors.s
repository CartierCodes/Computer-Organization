		addi x1, x2, x3			# not a number
label:	        jal				# no label
		ori x2, 99, 0xAB		# invalid register
		bne x2, x1, not_found		# nonexistant label
		addi x3, x2, 0x80808080		# number too large
# Can you think of any others?
