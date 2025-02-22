from graphviz import Digraph

def create_lexer_diagram():
    dot = Digraph(comment='Lexer Transition Diagram')
    dot.attr(rankdir='LR', splines='ortho')  # Left-to-right layout
    
    # Create special states
    dot.node('Start', shape='point')
    dot.node('Accept', shape='doublecircle')
    
    # Main token recognition paths
    with dot.subgraph(name='cluster_0') as c:
        c.attr(label='Identifier', color='blue')
        c.node('IdState1')
        c.edge('Start', 'IdState1', label='[a-zA-Z_]')
        c.edge('IdState1', 'IdState1', label='[a-zA-Z0-9_]')
        c.edge('IdState1', 'Accept', label='Other')

    with dot.subgraph(name='cluster_1') as c:
        c.attr(label='Integer Literal', color='green')
        c.node('IntState1')
        c.edge('Start', 'IntState1', label='[0-9]')
        c.edge('IntState1', 'IntState1', label='[0-9]')
        c.edge('IntState1', 'Accept', label='Other')

    with dot.subgraph(name='cluster_2') as c:
        c.attr(label='Character Literal', color='purple')
        c.node('CharState1')
        c.node('CharState2')
        c.edge('Start', 'CharState1', label="'")
        c.edge('CharState1', 'CharState2', label="[^']")
        c.edge('CharState2', 'Accept', label="'")

    with dot.subgraph(name='cluster_3') as c:
        c.attr(label='Relational Operators', color='red')
        c.node('RelState1')
        c.edge('Start', 'RelState1', label='=,!,<,>')
        c.edge('RelState1', 'Accept', label='=')
        c.edge('RelState1', 'Accept', label='Other')

    # Direct punctuation transitions
    dot.edge('Start', 'Accept', label='; { } ( )', color='orange')
    
    return dot

# Generate and save diagram
lexer_diagram = create_lexer_diagram()
lexer_diagram.render('lexer_transitions', format='png', cleanup=True)
print("Diagram generated as lexer_transitions.png")