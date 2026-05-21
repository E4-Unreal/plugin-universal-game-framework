#include "Misc/AutomationTest.h"
#include "Mocks/MainMenuModelMock.h"
#include "UI/Interfaces/MainMenuModelInterface.h"
#include "UI/ViewModels/MainMenuViewModel.h"

BEGIN_DEFINE_SPEC(FMainMenuViewModelSpec, "Plugins.UniversalGameFramework.UI.ViewModels.MainMenu", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
    UMainMenuViewModel* ViewModel;
    UMainMenuModelMock* Model;
END_DEFINE_SPEC(FMainMenuViewModelSpec)

void FMainMenuViewModelSpec::Define()
{
    BeforeEach([this]()
    {
        // Create ViewModel and Model
        ViewModel = NewObject<UMainMenuViewModel>();
        Model = NewObject<UMainMenuModelMock>();

        // Validate model interface implementation
        TestTrue(TEXT("Model->Implements<UMainMenuModelInterface>()"), Model->Implements<UMainMenuModelInterface>());

        // Inject Model into ViewModel
        if (TestTrue(TEXT("ViewModel->Implements<UModelInjectableInterface>()"), ViewModel->Implements<UModelInjectableInterface>()))
        {
            IModelInjectableInterface::Execute_SetModel(ViewModel, Model);
        }
    });

    Describe("Initialization", [this]()
    {
        It("GameTitleText", [this]()
        {
            const FString ExpectedTitle = TEXT("Test Game Title");

            TestEqual(TEXT("GameTitleText"), ViewModel->GetGameTitleText().ToString(), ExpectedTitle);
        });

        It("VersionText", [this]()
        {
            const FString ExpectedVersion = TEXT("99.99.99");

            TestEqual(TEXT("VersionText"), ViewModel->GetVersionText().ToString(), ExpectedVersion);
        });
    });

    Describe("Interaction", [this]()
    {
        It("StartButton", [this]()
        {
            ViewModel->HandleOnStartButtonClicked();

            TestTrue(TEXT("Model->IsStartGameRequested"), Model->IsStartGameRequested());
        });

        It("OptionsButton", [this]()
        {
            ViewModel->HandleOnOptionsButtonClicked();

            TestTrue(TEXT("Model->IsOptionsPanelOpen"), Model->IsOptionsPanelOpen());
        });

        It("ExitButton", [this]()
        {
            ViewModel->HandleOnExitButtonClicked();

            TestTrue(TEXT("Model->IsExitGameRequested"), Model->IsExitGameRequested());
        });
    });

    AfterEach([this]()
    {
        ViewModel = nullptr;
        Model = nullptr;
    });
}
