void checkWave()
{
    for(int i = 0; i < 30; i++)
        if(enemy[i]->alive == true)
        return;
    resetWave();
}

void resetWave()
{

}
