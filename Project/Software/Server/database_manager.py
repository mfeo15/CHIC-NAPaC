import sqlite3

def show(all_rows):
	for row in all_rows:
		print()
		for field in row:
			print(' {}'.format(field), end="")


def query_select(q, fetchone=False):
	db = sqlite3.connect('db.db')

	cursor = db.cursor()
	cursor.execute(q)
	result = cursor.fetchall() if not fetchone else cursor.fetchone()

	db.close()

	return result


def query_update(q):
	db = sqlite3.connect('db.db')

	cursor = db.cursor()
	cursor.execute(q)

	db.commit()
	db.close()

	return True if cursor.rowcount==1 else False


def query_insert(q):
	db = sqlite3.connect('db.db')

	cursor = db.cursor()
	cursor.execute(q)

	db.commit()
	db.close()


def ToyParentAssociationExist(first_id, second_id):

	if first_id.startswith('P'):
		query = "SELECT * FROM peluches WHERE pid='{p1}' AND associated_uid='{p2}' ".format(p1=first_id, p2=second_id)
	else:
		query = "SELECT * FROM peluches WHERE pid='{p1}' AND associated_uid='{p2}' ".format(p1=second_id, p2=first_id)

	return True if query_select(query, fetchone=True) is not None else False


def associateParent2Toy(parent_id, toy_id):

	query = "UPDATE peluches SET associated_uid = '{set}' WHERE pid = '{cond}' ".format(set=parent_id, cond=toy_id)

	return query_update(query)


def disassociateParent2Toy(toy_id):

	query = "UPDATE peluches SET associated_uid = NULL WHERE pid = '{cond}' ".format(cond=toy_id)

	return query_update(query)

def isParentUsernameAvailable(username):

	result = query_select("SELECT * FROM users WHERE username = '{}'".format(username), fetchone=True)

	return True if result is None else False

def registerNewParent(username, password):

	last_used_uid = query_select("SELECT MAX(uid) FROM users", fetchone=True)[0]
	new_available_uid = "U{}".format(int(last_used_uid[1:]) + 1)

	query = "INSERT INTO users(uid, username, password) VALUES('{p1}', '{p2}', '{p3}')".format(p1=new_available_uid, p2=username, p3=password)

	print(query)

	query_insert(query)

	return new_available_uid


if __name__ == "__main__":
	print("Standalone execution")
	'''
	show( query_select("SELECT * FROM peluches") )

	associateParent2Toy(parent_id="U314", toy_id="P123")

	show( query_select("SELECT * FROM peluches") )

	disassociateParent2Toy(toy_id="P123")

	show( query_select("SELECT * FROM peluches") )
	'''

	show( query_select("SELECT * FROM users") )

	print(ToyParentAssociationExist("U314", "P123"))