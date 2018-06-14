# Example string message that could be retrieved from a stream 
# N.B. control char STX, RS, US, EOT are not visible
message = Message.from_string("0000 U123 P314 2003 1 7")

print(message.destination)      # console> U123
print(message.source)           # console> P314
print(message.msg_id)           # console> 2003
print(message.parameters)       # console> ['7']