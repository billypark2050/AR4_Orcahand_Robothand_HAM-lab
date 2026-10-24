"""Tiny SVG builder shared by all four diagrams (classes are styled by the page CSS)."""
import html

class Svg:
    def __init__(self, uid):
        self.uid, self.out = uid, []

    def esc(self, s):
        return html.escape(s)

    def box(self, x, y, w, h, title, sub=None, grp="ros", badge=None, pill=False,
            dashed=False, faded=False, sub2=None, align="start"):
        cls = f"b {grp}" + (" dash" if dashed else "") + (" fade" if faded else "")
        self.out.append(f'<rect class="{cls}" x="{x}" y="{y}" width="{w}" height="{h}" rx="{h/2 if pill else 8}"/>')
        tx = x + 14
        if badge:
            bw = 30 if badge == "ROS" else 26
            bcls = "badge rosb" if badge == "ROS" else "badge"
            self.out.append(f'<rect class="{bcls}{" fade" if faded else ""}" x="{x+10}" y="{y+11}" width="{bw}" height="16" rx="3"/>'
                            f'<text class="bt" x="{x+10+bw/2}" y="{y+23}" text-anchor="middle">{badge}</text>')
            tx = x + 18 + bw
        if pill or align == "middle":
            tx, anchor = x + w / 2, "middle"
        else:
            anchor = "start"
        lines = [l for l in (sub, sub2) if l]
        ty = y + (h - 16 * len(lines)) / 2 + 6 if lines else y + h / 2 + 5
        op = ' opacity="0.55"' if faded else ""
        self.out.append(f'<text class="t" x="{tx}" y="{ty}" text-anchor="{anchor}"{op}>{self.esc(title)}</text>')
        for i, l in enumerate(lines):
            self.out.append(f'<text class="s" x="{tx}" y="{ty + 17 + 15*i}" text-anchor="{anchor}"{op}>{self.esc(l)}</text>')

    def frame(self, x, y, w, h, label, grp="ros", pos="top"):
        self.out.append(f'<rect class="frame {grp}" x="{x}" y="{y}" width="{w}" height="{h}" rx="10"/>')
        ly = y + 18 if pos == "top" else y + h - 10
        self.out.append(f'<text class="fl {grp}t" x="{x+12}" y="{ly}">{self.esc(label)}</text>')

    def line(self, pts, kind, label=None, lx=None, ly=None, anchor="start", both=False, end=True):
        d = " ".join(f"{x},{y}" for x, y in pts)
        me = f' marker-end="url(#{self.uid}-{kind})"' if end else ""
        ms = f' marker-start="url(#{self.uid}-{kind})"' if both else ""
        self.out.append(f'<polyline class="a {kind}" points="{d}"{me}{ms}/>')
        if label:
            self.out.append(f'<text class="al {kind}l" x="{lx}" y="{ly}" text-anchor="{anchor}">{self.esc(label)}</text>')

    def system(self, x, y, w, h, label, lx=None, ly=None, anchor="start"):
        """ROS 2 system boundary, drawn underneath everything else."""
        lx = x + 14 if lx is None else lx
        ly = y + 20 if ly is None else ly
        self.out.insert(0, f'<rect class="rossys" x="{x}" y="{y}" width="{w}" height="{h}" rx="14"/>'
                           f'<text class="rossyst" x="{lx}" y="{ly}" text-anchor="{anchor}">{self.esc(label)}</text>')

    def text(self, x, y, s, cls="layer", anchor="start"):
        self.out.append(f'<text class="{cls}" x="{x}" y="{y}" text-anchor="{anchor}">{self.esc(s)}</text>')

    def rect(self, x, y, w, h, cls):
        self.out.append(f'<rect class="{cls}" x="{x}" y="{y}" width="{w}" height="{h}"/>')

    def hline(self, x1, x2, y, cls="sep"):
        self.out.append(f'<line class="{cls}" x1="{x1}" y1="{y}" x2="{x2}" y2="{y}"/>')

    def vline(self, x, y1, y2, cls="life"):
        self.out.append(f'<line class="{cls}" x1="{x}" y1="{y1}" x2="{x}" y2="{y2}"/>')

    def defs(self):
        kinds = ["cmd", "fb", "phys", "loop", "topic", "action", "service", "call", "include", "ret", "serial", "iface", "seq", "seqs"]
        m = "".join(
            f'<marker id="{self.uid}-{k}" viewBox="0 0 10 10" refX="9" refY="5" markerWidth="7" markerHeight="7" '
            f'orient="auto-start-reverse"><path class="mk {k}k" d="M0,0 L10,5 L0,10 z"/></marker>' for k in kinds)
        return f"<defs>{m}</defs>"

    def render(self, w, h, label):
        return (f'<svg viewBox="0 0 {w} {h}" role="img" aria-label="{self.esc(label)}">'
                + self.defs() + "\n".join(self.out) + "</svg>")
