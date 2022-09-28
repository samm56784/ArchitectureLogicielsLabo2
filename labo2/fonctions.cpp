#pragma once
#include <conio.h>
#include "fonctions.h"

void ToucheEntrée(HRESULT hr, IGraphBuilder* pGraph, IMediaControl* pControl, IMediaEvent* pEvent, IMediaSeeking* pSeeking)
{
    REFERENCE_TIME rtNow = 0, rtEnd;
    char lettre = 'Z';
    FILTER_STATE state;
    long evCode;
    hr = pSeeking->GetPositions(NULL, &rtEnd);
    while (lettre!='Q')
    {
        lettre = _getch();
        lettre = toupper(lettre);
        switch (lettre)
        {
        case 'A':
            hr = pSeeking->SetRate(1.25);
            cout << "A - Avance rapide (1,25x)\n";
            break;
        case 'P':
            hr = pControl->GetState(0, (OAFilterState*)&state);
            if (state == State_Paused)
            {
                hr = pControl->Run();
                cout << "P - Play\n";
            }
            else
            {
                hr = pControl->Pause();
                cout << "P - Pause\n";
            }
            break;
        case 'R':
            hr = pSeeking->SetRate(1.0);
            hr = pSeeking->SetPositions(&rtNow, AM_SEEKING_AbsolutePositioning, &rtEnd, AM_SEEKING_AbsolutePositioning);
            hr = pControl->Run();
            cout << "R - Retour au debut\n";
            break;
        case 'Q':
           // pControl->Release();
           // pEvent->Release();
           // pGraph->Release();
            //CoUninitialize();
            //return;
            break;
        default:
            cout << "Caractere invalide !\n";
            break;
        }

    }

}