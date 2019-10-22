from graphics import *
from nodes import Node
from time import sleep
from math import sqrt
from random import randint

def create_node(node, radius):
	try:
		circle = Circle(Point(node.x, node.y), radius)
	except GraphicsError:
		circle = Circle(Point(node.x, node.y), 6)
	text = Text(Point(node.x, node.y), str(node.name))
	return ({'circle': circle, 'text': text})

def draw_nodes(nodes, radius, win):
	for node in nodes:
		n = create_node(node, radius)
		if node.start:
			n['circle'].setFill(color_rgb(23, 173, 173))
		elif node.end:
			n['circle'].setFill(color_rgb(191, 76, 69))
		else:
			n['circle'].setFill(color_rgb(30, 30, 30))
		n['circle'].setOutline('white')
		n['text'].setFill('white')
		try:
			n['text'].setSize(int(radius / 2))
		except GraphicsError:
			n['text'].setSize(6)
		try:
			n['circle'].draw(win)
			n['text'].draw(win)
		except GraphicsError:
			exit()

def create_link(link, nodes):
	for node in nodes:
		if node.name == link[0]:
			p1 = Point(node.x, node.y)
		elif node.name == link[1]:
			p2 = Point(node.x, node.y)
	p1 = Point(p1.x, p1.y)
	p2 = Point(p2.x, p2.y)
	return Line(p1, p2)

def draw_links(links, nodes, win):
	for link in links:
		try:
			link = create_link(link, nodes)
		except UnboundLocalError:
			exit('Invalid input.')
		link.setFill('white')
		try:
			link.draw(win)
		except GraphicsError:
			exit()

def min_max_coords(nodes):
	min_x = max_x = nodes[0].x
	min_y = max_y = nodes[0].y
	for node in nodes:
		if node.x > max_x: max_x = node.x
		if node.y > max_y: max_y = node.y
		if node.x < min_x: min_x = node.x
		if node.y < min_y: min_y = node.y
	return {'min_x': min_x, 'max_x': max_x, 'min_y': min_y, 'max_y': max_y}

def parse_input():
	nodes = []
	links = []
	ant_tacts = []

	start = False
	end = False
	try:
		ants_count = int(input())
	except (EOFError, ValueError):
		exit('Invalid input')
	while True:
		try:
			inp = input()
		except EOFError:
			break
		if len(inp) == 0: continue
		if inp == '##start': start = True
		elif inp == '##end': end = True
		elif inp[0] == '#': continue
		elif inp[0] == 'L':
			ants_instructions = []
			ants_input = inp.split()
			for ant in ants_input:
				ins = ant[1:].split('-')
				try:
					int(ins[0])
				except ValueError:
					exit('Invalid instruction.')
				if len(ins) == 2:
					ants_instructions.append(ant[1:].split('-'))
				else:
					exit('Invalid instruction.')
			ant_tacts.append(ants_instructions)
			for instruction in ants_instructions:
				node_exists = False
				for node in nodes:
					if instruction[1] == node.name:
						node_exists = True
				if not node_exists:
					exit('Invalid instruction.')
		elif len(inp.split()) == 3:
			params = inp.split()
			try:
				nodes.append(Node(params[0], int(params[1]), int(params[2]), start, end))
			except ValueError:
				exit('Invalid room declaration.')
			start = end = False
		elif inp.count('-') == 1 and len(inp.split()) == 1:
			rooms = inp.split('-')
			links.append((rooms[0], rooms[1]))
	return nodes, links, ants_count, ant_tacts

def calc_size(coords, nodes, offset):
	height = coords['max_y'] - coords['min_y'] + 0.01
	width = coords['max_x'] - coords['min_x'] + 0.01
	if width > height:
		mp = (1200 - offset * 2) / width
	else:
		mp = (1200 - offset * 2) / height
	for node in nodes:
		node.x = (node.x - coords['min_x']) * mp + offset
		node.y = (node.y - coords['min_y']) * mp + offset
	height = height * mp + offset * 2
	width = width * mp + offset * 2
	return width, height

def get_start_coords(nodes):
	for node in nodes:
		if node.start:
			return({'x': node.x, 'y':node.y})

def create_ants(cnt, coords, radius):
	ants = []
	for ant in range(cnt):
		ant_text = Text(Point(coords['x'], coords['y']), str(ant + 1))
		ant = Circle(Point(coords['x'], coords['y']), radius)
		ant.setFill('yellow')
		ants.append({'ant': ant, 'text': ant_text})
	return ants

def draw_ants(cnt, coords, radius, win):
	ants = create_ants(cnt, coords, radius)
	for ant in ants:
		ant['ant'].draw(win)
		ant['text'].draw(win)
	return ants

def move_ants(ants, tact, nodes, win, speed = 0):
	color = color_rgb(randint(25, 255), randint(25, 255), randint(25, 255))
	flag = True
	dx = {}
	dy = {}
	for move in tact:
		for node in nodes:
			if node.name == move[1]:
				dest = Point(node.x, node.y)
		ant = ants[int(move[0]) - 1]
		dx[move[0]] = (dest.getX() - ant['ant'].getCenter().getX()) / 50
		dy[move[0]] = (dest.getY() - ant['ant'].getCenter().getY()) / 50
	while flag:
		flag = False
		for move in tact:
			for node in nodes:
		 		if node.name == move[1]:
		 			dest = Point(node.x, node.y)
			ant = ants[int(move[0]) - 1]
			ant['ant'].setFill(color)
			if (round(ant['ant'].getCenter().getX()), round(ant['ant'].getCenter().getY())) != (round(dest.getX()), round(dest.getY())):
				ant['ant'].undraw()
				ant['text'].undraw()
				ant['ant'].move(dx[move[0]], dy[move[0]])
				ant['text'].move(dx[move[0]], dy[move[0]])
				try:
					ant['ant'].draw(win)
					ant['text'].draw(win)
				except GraphicsError:
					exit()
				flag = True
		win.update()

def main():
	nodes, links, ants_count, ants_tacts = parse_input()
	coords = min_max_coords(nodes)
	width, height = calc_size(coords, nodes, 100)
	win = GraphWin('lem-in', width, height, autoflush = False)
	win.setBackground(color_rgb(8, 17, 23))
	win.update()
	radius = 1120 / sqrt((len(nodes) + 10) * 4) / 3
	draw_links(links, nodes, win)
	draw_nodes(nodes, radius, win)
	win.update()
	if ants_count:
		start_coords = get_start_coords(nodes)
		ants = draw_ants(ants_count, start_coords, radius / 2, win)
		win.update()
		try:
			win.getMouse()
		except GraphicsError:
			exit()
		for tact in ants_tacts:
			move_ants(ants, tact, nodes, win)
			sleep(.3)
	try:
		while win.getKey() != 'Escape':
			pass
	except GraphicsError:
		pass
	exit()

if __name__ == '__main__':
	try:
		main()
	except KeyboardInterrupt:
		exit()