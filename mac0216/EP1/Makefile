CC:=./macas
LK:=./maclk

SRCDIR:=src
OBJDIR:=obj
EXEDIR:=bin

%.maco: $(SRCDIR)/%.macal
	$(CC) $^
	mv $(SRCDIR)/$@ $(OBJDIR)

$(EXEDIR)/9793694.mac: $(OBJDIR)/9793694.maco $(OBJDIR)/loadt.maco $(OBJDIR)/prl.maco $(OBJDIR)/strint.maco
	$(LK) $@ $^
