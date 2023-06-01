import sys
import copy

class edge:
    def __init__(self, Label, u, v) -> None:
        self.label = Label
        self.visited = False
        self.U = u
        self.V = v

class vertex:
    def __init__(self, Label) -> None:
        self.neighbors = []
        self.visited = False

class graph:
    def __init__(self, ver_num) -> None:
        self.V = {}
        for i in range(ver_num):    self.V[i + 1] = vertex(Label = i + 1)
        self.E = {}
        self.edge_num = int(0)
        self.get_edge_label = {}
        
    def add_edge(self, u : int, v : int) -> None:
        if u == v:
            return 
        self.V[u].neighbors.append(v)
        self.V[v].neighbors.append(u)
        try:
            if u not in self.get_edge_label.keys():    self.get_edge_label[u] = {v : self.edge_num}
            else:    self.get_edge_label[u].update({v : self.edge_num})
            if v not in self.get_edge_label.keys():   self.get_edge_label[v] = {u : self.edge_num}
            else:    self.get_edge_label[v].update({u : self.edge_num})
        except:
            pass
        self.E[self.edge_num] = edge(Label = self.edge_num, u = u, v = v)
        self.edge_num += 1

    def init_dfs(self) -> None:
        for v in self.V.values():    v.visited = False
        for e in self.E.values():    e.visited = False

    def _get_path(self, From : int, To : list) -> list:
        if From in To:    return [From]
        rec = []
        ret = []
        self.V[From].visited = True
        for v in self.V[From].neighbors:
            if not self.V[v].visited:
                rec = self._get_path(From = v, To = To)
            if len(rec) != 0:
                ret = [From] + rec
                break
        return ret
    
    def get_path(self, From : int, To : list) -> list:
        self.init_dfs()
        return self._get_path(From, To)
    
    def get_circle(self) -> list:
        self.init_dfs()
        end = self.V[1].neighbors[0]
        self.V[1].neighbors.pop(0)
        ret = self.get_path(From = 1, To = [end])
        self.V[1].neighbors.append(end)
        return ret

class face(graph):
    def __init__(self, B : list, Label : int) -> None:
        super().__init__(0)
        self.face_label = Label
        for i in B:    self.V[i] = vertex(i)
        for i in range(len(B) - 1):    self.add_edge(B[i], B[i + 1])
        self.add_edge(B[-1], B[0])
        self.get_edge_label = None

    def change_boundary(self, old_boundary, new_boundary) -> None:
        if len(new_boundary) > 2:
            for v in new_boundary[1 : -1]:
                self.V[v] = vertex(v)
        for i in range(len(new_boundary) - 1):    self.add_edge(new_boundary[i], new_boundary[i + 1])
        self.V[new_boundary[0]].neighbors.remove(old_boundary[-2])
        self.V[new_boundary[-1]].neighbors.remove(old_boundary[1])
        if len(old_boundary) > 2:
            for v in old_boundary[1 : -1]:
                self.V.pop(v)

class H_seg(graph):
    def __init__(self, start_point, G : graph, H) -> None:
        super().__init__(0)
        self.near_faces = []
        if type(H) == int:
            self.connect_point = [start_point, H]
            self.V = {start_point : vertex(start_point), H : vertex(H)}
            self.add_edge(start_point, H, Label = G.get_edge_label[start_point][H])
        else:
            self.connect_point = []
            self.find_hseg(start_point, G, H)
    
    def add_edge(self, u, v, Label):
        if u == v:    return 
        self.V[u].neighbors.append(v)
        self.V[v].neighbors.append(u)
        if u not in self.get_edge_label.keys():    self.get_edge_label[u] = {v : Label}
        else:    self.get_edge_label[u].update({v : Label})
        if v not in self.get_edge_label.keys():    self.get_edge_label[v] = {u : Label}
        else:   self.get_edge_label[v].update({u : Label})
        self.E[Label] = edge(Label = Label, u = u, v = v)

    def find_hseg(self, Current, G : graph, H):
        G.V[Current].visited = True
        if Current not in self.V.keys():    self.V[Current] = vertex(Current)
        for v in G.V[Current].neighbors:
            G.E[G.get_edge_label[Current][v]].visited = True
            if v not in self.V.keys():    self.V[v] = vertex(v)
            self.add_edge(Current, v, Label = G.get_edge_label[Current][v])
            if v not in H["vertexs"] and not G.V[v].visited:    self.find_hseg(v, G, H)
            if v in H["vertexs"] and v not in self.connect_point:    self.connect_point.append(v)

def DMP(G  : graph) -> bool:
    H = {"vertexs" : [], "edges" : []}
    first_circle = G.get_circle()
    faces = {}
    faces[0] = face(first_circle, 0)
    faces[1] = face(first_circle, 1)
    face_num = int(2)
    H["vertexs"] += first_circle
    for i in range(len(first_circle)-1):    H["edges"] += [G.get_edge_label[first_circle[i]][first_circle[i+1]]]
    H["edges"] += [G.get_edge_label[first_circle[0]][first_circle[-1]]]
    while len(H["vertexs"]) < len(G.V) or len(H["edges"]) < len(G.E):
        B = None
        G.init_dfs()
        H_segs = []
        for v in H["vertexs"]:
            for u in G.V[v].neighbors:
                if u not in H["vertexs"] and not G.V[u].visited:
                    H_segs.append(H_seg(u, G, H))
                elif G.get_edge_label[v][u] not in H["edges"] and not G.E[G.get_edge_label[v][u]].visited:
                    G.E[G.get_edge_label[v][u]].visited = True
                    H_segs.append(H_seg(v, G, u))
        for hseg in H_segs:
            for key, F in faces.items():
                flag = True
                for i in hseg.connect_point:
                    if i not in F.V.keys():
                        flag = False
                if flag:
                    hseg.near_faces.append(key)
            if len(hseg.near_faces) == 0:
                return False
            if len(hseg.near_faces) == 1:
                B = hseg
        if not B:
            B = H_segs[0]
        to = copy.deepcopy(B.connect_point)
        to.pop(0)
        path_in_B = B.get_path(From = B.connect_point[0], To = to)
        f = B.near_faces[0]
        path_in_f = faces[f].get_path(From = path_in_B[-1], To = [path_in_B[0]])
        old_boundary = copy.deepcopy(path_in_f)
        faces[f].change_boundary(old_boundary, path_in_B)
        new_face = []
        if len(path_in_f) <= 2:
            new_face = path_in_B
        elif len(path_in_B) <= 2:
            new_face = path_in_f
        else:
            new_face = copy.deepcopy(path_in_B + path_in_f[1 : -1])
        faces[face_num] = face(new_face, face_num)
        face_num += 1
        for i in range(len(path_in_B) - 1):
            if path_in_B[i] not in H["vertexs"]:
                H["vertexs"].append(path_in_B[i])
            if G.get_edge_label[path_in_B[i]][path_in_B[i+1]] not in H["edges"]:
                H["edges"].append(G.get_edge_label[path_in_B[i]][path_in_B[i+1]])
        if path_in_B[-1] not in H["vertexs"]:
            H["vertexs"].append(path_in_B[-1])
    return True

if __name__ == "__main__":
    sys.setrecursionlimit(5000)
    data = input().split()
    n = int(data[0])
    m = int(data[1])
    G = graph(n)
    G.init_dfs()
    for i in range(m):
        data = input().split()
        a = int(data[0])
        b = int(data[1])
        G.add_edge(a, b)
    if DMP(G):
        print(1)
    else:
        print(0)