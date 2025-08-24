
#include <Platform/Windows/WinDialogEventHandler.hpp>

#include <propvarutil.h>  
#include <propkey.h>      
#include <propidl.h>   

// IFileDialogEvents methods
// This method gets called when the file-type is changed (combo-box selection changes).
// For sample sake, let's react to this event by changing the properties show.
HRESULT DialogEventHandler::OnTypeChange(IFileDialog* pfd)
{
    IFileSaveDialog* pfsd;
    HRESULT hr = pfd->QueryInterface(&pfsd);
    if (SUCCEEDED(hr))
    {
        UINT uIndex;
        hr = pfsd->GetFileTypeIndex(&uIndex);   // index of current file-type
        if (SUCCEEDED(hr))
        {
            IPropertyDescriptionList* pdl = NULL;

            switch (uIndex)
            {
            case INDEX_WORDDOC:
                // When .doc is selected, let's ask for some arbitrary property, say Title.
                hr = PSGetPropertyDescriptionListFromString(L"prop:System.Title", IID_PPV_ARGS(&pdl));
                if (SUCCEEDED(hr))
                {
                    // FALSE as second param == do not show default properties.
                    hr = pfsd->SetCollectedProperties(pdl, FALSE);
                    pdl->Release();
                }
                break;

            case INDEX_WEBPAGE:
                // When .html is selected, let's ask for some other arbitrary property, say Keywords.
                hr = PSGetPropertyDescriptionListFromString(L"prop:System.Keywords", IID_PPV_ARGS(&pdl));
                if (SUCCEEDED(hr))
                {
                    // FALSE as second param == do not show default properties.
                    hr = pfsd->SetCollectedProperties(pdl, FALSE);
                    pdl->Release();
                }
                break;

            case INDEX_TEXTDOC:
                // When .txt is selected, let's ask for some other arbitrary property, say Author.
                hr = PSGetPropertyDescriptionListFromString(L"prop:System.Author", IID_PPV_ARGS(&pdl));
                if (SUCCEEDED(hr))
                {
                    // TRUE as second param == show default properties as well, but show Author property first in list.
                    hr = pfsd->SetCollectedProperties(pdl, TRUE);
                    pdl->Release();
                }
                break;
            }
        }
        pfsd->Release();
    }
    return hr;
}

// IFileDialogControlEvents
// This method gets called when an dialog control item selection happens (radio-button selection. etc).
// For sample sake, let's react to this event by changing the dialog title.
HRESULT DialogEventHandler::OnItemSelected(IFileDialogCustomize* pfdc, DWORD dwIDCtl, DWORD dwIDItem)
{
    IFileDialog* pfd = NULL;
    HRESULT hr = pfdc->QueryInterface(&pfd);
    if (SUCCEEDED(hr))
    {
        if (dwIDCtl == CONTROL_RADIOBUTTONLIST)
        {
            switch (dwIDItem)
            {
            case CONTROL_RADIOBUTTON1:
                hr = pfd->SetTitle(L"Longhorn Dialog");
                break;

            case CONTROL_RADIOBUTTON2:
                hr = pfd->SetTitle(L"Vista Dialog");
                break;
            }
        }
        pfd->Release();
    }
    return hr;
}