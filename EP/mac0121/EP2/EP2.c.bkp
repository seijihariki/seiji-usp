#include <stdlib.h>
#include <stdio.h>

/* Outros typedefs úteis */
typedef unsigned int uint;
typedef unsigned char ubyte;
typedef char byte;

/* Definição de booleanas */
typedef ubyte bool;
const bool false = 0;
const bool true = 1;

typedef struct
{
    uint x, y;
} coords;

typedef struct 
{
    coords init;
    ubyte direction;
} move;

/* Mesa */
/*  Dados armazenados do seguinte modo:
       0          1          2          3         4
    0  [0][0]     [1][0]     [2][0]     ...       [szx-1][0]
    1  [0][1]     [1][1]     [2][1]     ...       [szx-1][1]
    2  [0][2]     [1][2]     [2][2]     ...       [szx-1][2]
    3  ...        ...        ...  
    4  [0][szy-1] [1][szy-1] [2][szy-1]
*/

typedef struct
{
    byte **data;
    uint szx, szy;
} board;

coords movedef[4];

/* Representar movimentos em sentido horário começando com "para cima" 0*/
void init ()
{
    /* Cima */
    movedef[0].x = 0;
    movedef[0].y = -2;
    /* Direita */
    movedef[1].x = 2;
    movedef[1].y = 0;
    /* Baixo */
    movedef[2].x = 0;
    movedef[2].y = 2;
    /* Esquerda */
    movedef[3].x = -2;
    movedef[3].y = 0;
}

/* Criar mesa (retorna falso caso malloc falhe.) */
bool bd_create (board *bd, uint szx, uint szy)
{
    uint i;
    byte counter = 1;

    bd->data = malloc(sizeof(byte*)*szx);
    if(!bd->data) return false;

    for (i = 0; i < szx && i >= 0; i+=counter)
    {
        if(counter > 0) bd->data[i] = malloc(sizeof(byte)*szy);
        else free(bd->data[i]);
        if(!bd->data[i] && counter > 0) counter = -1;
    }

    if(counter < 0) free(bd->data);
    else
    {
        bd->szx = szx;
        bd->szy = szy;
    }
    return counter > 0;
}

/* Retorna valor nas coordenadas */
byte bd_at(board *bd, coords cr)
{
    return bd->data[cr.x][cr.y];
}

/* Atribui um valor a certas coordenadas */
void bd_set(board *bd, coords cr, byte val)
{
    bd->data[cr.x][cr.y] = val;
}

/* Copiar mesa (retorna falso caso malloc falhe.) */
bool bd_copy (board *bd, board *orig)
{
    uint i, k;
    byte counter = 1;

    bd->data = malloc(sizeof(byte*)*orig->szx);
    if(!bd->data) return false;

    for (i = 0; i < orig->szx && i >= 0; i+=counter)
    {
        if(counter > 0){
            bd->data[i] = malloc(sizeof(byte)*orig->szy);
            for(k = 0; k < orig->szy; k++)bd->data[i][k] = orig->data[i][k];
        }
        else free(bd->data[i]);
        if(!bd->data[i] && counter > 0) counter = -1;
    }

    if(counter < 0) free(bd->data);
    else
    {
        bd->szx = orig->szx;
        bd->szy = orig->szy;
    }
    return counter > 0;
}

/* Retorna as coordenadas finais de um movimento */
bool validate_coords (board *bd, coords cr)
{
    return (cr.x >= 0 && cr.x < bd->szx && cr.y >= 0 && cr.y < bd->szy) && bd->data[cr.x][cr.y];
}

/* Retorna as coordenadas finais de um movimento */
coords end_move (move mv)
{
    coords res;
    res.x = mv.init.x;
    res.y = mv.init.y;
    res.x += movedef[mv.direction].x;
    res.y += movedef[mv.direction].y;
    return res;
}

/* Retorna se as mesas são iguais */
bool bd_eq (board *bd1, board *bd2)
{
    uint x, y;
    if (bd1->szx == bd2->szx && bd1->szy == bd2->szy)
    {
        for (x = 0; x < bd1->szx; x++)
        {
            for (y = 0; y < bd1->szy; y++)
            {
                coords cr;
                cr.x = x;
                cr.y = y;
                if(bd_at(bd1, cr) != bd_at(bd2, cr)) return false;
            }
        }
    } else return false;
    return true;
}

void bd_print (board *bd)
{
    uint x, y;
    for (y = 0; y < bd->szy; y++)
    {
        for (x = 0; x < bd->szx; x++)
        {
            coords cr;
            cr.x = x;
            cr.y = y;
            byte c = bd_at(bd, cr);
            printf("%s\t", c < 0?"\e[31mo\e[0m":c?"p":" ");
        }
        printf("\n\n");
    }
    printf("\n\n\n");
}


/* Aplica movimento */
bool apply_move (board *bd, move mv)
{
    coords end, middle, init;
    init = mv.init;
    end = end_move(mv);
    middle.x = (end.x + init.x)/2;
    middle.y = (end.y + init.y)/2;
    if((validate_coords(bd, end) && validate_coords(bd, init) && validate_coords(bd, middle)) &&
        (bd_at(bd, init) == 1 && bd_at(bd, end) == -1 && bd_at(bd, middle) == 1))
    {
        bd_set(bd, middle, -1);
        bd_set(bd, init, -1);
        bd_set(bd, end, 1);
        return true;
    }
    else return false;
}

/* Desfaz movimento */
bool undo_move (board *bd, move mv)
{
    coords end, middle, init;
    init = mv.init;
    end = end_move(mv);
    middle.x = (end.x + init.x)/2;
    middle.y = (end.y + init.y)/2;
    if((validate_coords(bd, end) && validate_coords(bd, init) && validate_coords(bd, middle)) &&
        (bd_at(bd, init) == -1 && bd_at(bd, end) == 1 && bd_at(bd, middle) == -1))
    {
        bd_set(bd, middle, 1);
        bd_set(bd, init, 1);
        bd_set(bd, end, -1);
        return true;
    }
    else return false;
    return true; 
}

/* Liberar memória da mesa */
void bd_free (board *bd)
{
    uint i;
    for (i = 0; i < bd->szy; i++) free (bd->data[i]);
    free (bd->data);
    bd->data = 0;
}

/* Stack */
typedef struct
{
    move *data;
    uint top, size;
} stack;

bool stack_create (stack *st, uint size)
{
    move *data = (move*) malloc(sizeof(move)*size);
    st->data = data;
    if (data) st->size = size;
    st->top = 0;
    return data == 0;
}

bool stack_push (stack *st, move item)
{
    if (st->size == st->top) return false;
    st->data[st->top++] = item;
    return true;
}

bool stack_pop (stack *st, move *item)
{
    if (!st->top) return false;
    *item = st->data[--st->top];
    return true;
}

void stack_print (stack *st)
{
    int i;
    printf("Stack is now:\n");
    for (i = st->top-1; i >= 0; i--){
        move item = st->data[i];
        printf("item %d is\t(%u, %u) and %u\n", i, item.init.x, item.init.y, item.direction);
    }
}

bool stack_back (stack *st, move *item)
{
    if (!st->top) return false;
    *item = st->data[st->top - 1];
    return true;
}

bool stack_empty (stack *st)
{
    return !st->top;
}

void stack_free (stack *st)
{
    free(st->data);
}

/* Código para resolver o resta 1 do modo descrito */
bool resta_um (stack *st, board *bd)
{
    board inv; /* Manter a mesa invertida (mesa alvo) */
    bd_copy(&inv, bd);
    uint x, y;
    ubyte d = 0;

    /* Criar mesa invertida */
    for (x = 0; x < inv.szx; x++)
    {
        for (y = 0; y < inv.szy; y++)
        {
            coords cr;
            cr.x = x;
            cr.y = y;
            bd_set(&inv, cr, -bd_at(&inv, cr));
        }
    }

    /* Testar combinações (backtrack)*/
    move zmv;
    zmv.init.x = 0;
    zmv.init.y = 0;
    zmv.direction = -1;
    system("clear");
    bool m_undo = false;
    while (true)
    {
        move m = zmv;
        if (m_undo)
        {
            if(!stack_pop(st, &m)) break;
            undo_move(bd, m); 
        }

        bool ok = false;
        for (x = m.init.x; x < bd->szx && !ok; x++)
        {
            for (y = m.init.y; y < bd->szy && !ok; y++)
            {
                coords cr;
                cr.x = x;
                cr.y = y;
                for(d = m.direction + 1; d < 4 && !ok; d++)
                {
                    move now_mv;
                    now_mv.init = cr;
                    now_mv.direction = d;
                    if (bd_at(bd, cr) == 1 && apply_move(bd, now_mv))
                    {
                        /*printf("\033[%d;%dH", 0, 0);
                        bd_print(bd);*/
                        ok = true;
                        stack_push(st, now_mv);
                        if (bd_eq(&inv, bd)) return true; 
                    }
                } 
            }
        }
        m_undo = !ok;
    }
    return false;
}

int main ()
{
    uint maxmv = 50;
    uint szx = 0;
    uint szy = 0;

    uint x, y;

    stack moves;
    board bd;

    scanf("%d%d", &szy, &szx);

    init();

    stack_create (&moves, maxmv);
    bd_create(&bd, szx, szy);

    for (y = 0; y < szy; y++)
    {
        for (x = 0; x < szx; x++)
        {  
            coords cr;
            cr.x = x;
            cr.y = y;
            int b;
            scanf("%d", &b);
            bd_set(&bd, cr, b);
        }
    }

    bd_print(&bd);

    if(resta_um(&moves, &bd)) printf("Deu!!\n");
    else printf("Impossível!!\n");
    bd_free(&bd);
    stack_free(&moves);
    return 0;
}
