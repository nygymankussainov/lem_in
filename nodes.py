from dataclasses import dataclass

@dataclass
class	Node:
	name: str
	x: int
	y: int
	start: bool
	end: bool

	def __repr__(self):
		return ' '.join([self.name, str(self.x), str(self.y)])
