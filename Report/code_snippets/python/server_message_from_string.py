@classmethod
def from_string(cls, s):
    # Check basic correctness of the string-message
    if not (s.startswith(ASCII.STX) and s.endswith(ASCII.EOT)):
        return None
        
    # Obtain records from the string
    rec = s[1:-1].split(ASCII.RS)
    
    # If the there is NO parameters, build a message
    if len(rec) == 4:
        return cls(rec[1], rec[2], rec[3])

    # If the there extra parameters, retrieve their units first
    if len(rec) == 5:
        params = rec[4].split(ASCII.US)
        return cls(rec[1], rec[2], rec[3], params[1:])
        
    return None