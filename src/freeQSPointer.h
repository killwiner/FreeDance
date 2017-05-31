#ifndef FREEQSPOINTER_H
#define FREEQSPOINTER_H

// libère un tableau situé dans un QSharedPointer

template <typename T>
void do_delete(T table[])
{
    delete[] table;
}

#endif // FREEQSPOINTER_H
