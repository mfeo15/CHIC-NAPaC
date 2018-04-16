import ASCII

class Message(object):

	destination = None
	source = None
	msg_id = None
	parameters = []


	def __init__(self, dest, source, msg_id, parameters=[]):
		"""Constructor method of the class. """

		self.destination =dest
		self.source = source
		self.msg_id = msg_id
		self.parameters = parameters

	@classmethod
	def from_string(cls, s):
		
		if not (s.startswith(ASCII.STX) and s.endswith(ASCII.EOT)):
			return None

		records = s[1:-1].split(ASCII.RS)

		if len(records) == 4:
			return cls(records[1], records[2], records[3])

		if len(records) == 5:
			params = records[4].split(ASCII.US)
			return cls(records[1], records[2], records[3], params[1:])

		return None


	def to_string(self, delimiter=ASCII.RS):
		main = "{rs}{dest}{rs}{source}{rs}{msg_id}".format(rs=delimiter, dest=self.destination, source=self.source, msg_id=self.msg_id)

		if len(self.parameters) > 0:
			main += "{rs}{pc}".format(rs=delimiter, pc=len(self.parameters))
			for p in self.parameters:
				main += "{us}{p}".format(us=ASCII.US, p=p)

		output = "{stx}{l:04d}{main}{eot}".format(stx=ASCII.STX, l=(2+4+len(main)), main=main, eot=ASCII.EOT)

		return output

	def to_bytes(self, delimiter=""):
		message_str = self.to_string()

		output = ""
		for c in message_str:
			output += "{b:02d}{d}".format(b=ord(c), d=delimiter)

		return output



if __name__ == "__main__":
	print("Standalone execution", end="\n\n")

	m = "{stx}0000{rs}P123{rs}U314{rs}4242{rs}1{us}6666{eot}".format(stx=ASCII.STX, rs=ASCII.RS, us=ASCII.US, eot=ASCII.EOT)

	mes = Message.from_string(m)

	print(mes.to_string(delimiter=" "))